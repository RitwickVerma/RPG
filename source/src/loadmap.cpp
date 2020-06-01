#include "level.h"
#include "graphics.h"
#include "utils.h"

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/LayerGroup.hpp>
#include <tmxlite/Tileset.hpp>
#include <tmxlite/Property.hpp>
#include <tmxlite/Object.hpp>

struct tile_info
{
    const tmx::Tileset *tmxtileset;
    const tmx::Tileset::Tile *tmxtile;
    vector<Rectangle> collisionRectObjects;
    vector<Rectangle> thingRectObjects;
};


void Level::loadMap(Graphics &graphics, string mapName)
{
    string filepath=this->MAP_DIR+mapName;

    tmx::Map tmxmap;
    tmxmap.load(filepath);

    this->_mapTileSize = xyipair(tmxmap.getTileSize().x, tmxmap.getTileSize().y);
    this->_tileCount = xyipair(tmxmap.getTileCount().x, tmxmap.getTileCount().y);
    this->_size=xyipair(this->_tileCount * this->_mapTileSize);

    // this->_map = vector<vector<Tile>>(2, vector<Tile>(this->_tileCount.y * this->_tileCount.x, Tile()));
    unordered_map<int, tile_info> tileData;
    // Get all Tilesets and store them in the map _tilesets at key = firstGid
    for(auto &tileset : tmxmap.getTilesets())
    {
        string tilesetImagePath = tileset.getImagePath();
        this->_tilesets[tileset.getFirstGID()] = (Tileset(graphics.loadImage(tilesetImagePath), tileset.getFirstGID()));
        
        if(tileset.getName() != "terrain-map")
            for(auto &tile : tileset.getTiles())
            {
                tileData[tile.ID].tmxtileset = &tileset;
                tileData[tile.ID].tmxtile = &tile;
                for(auto &object : tile.objectGroup.getObjects())
                {
                    for(auto &prop : object.getProperties())
                    {
                        Rectangle r(ceil(object.getAABB().left), 
                                ceil(object.getAABB().top), 
                                ceil(object.getAABB().width),
                                ceil(object.getAABB().height));

                        if(prop.getName() == "collision" and prop.getBoolValue() == true)
                            tileData[tile.ID].collisionRectObjects.push_back(r);
                        if(prop.getName() == "thing" and prop.getBoolValue() == true)
                            tileData[tile.ID].thingRectObjects.push_back(r);
                    }
                }
            }
    }


    // Get all Layers and process them one by one
    auto &mapLayers = tmxmap.getLayers();
    auto &tilesets = tmxmap.getTilesets();
    for(auto &mapLayer : mapLayers)
    {
        // Ignore layers that aren't visible
        if(!mapLayer->getVisible())    continue; 

        if(mapLayer->getType() == tmx::Layer::Type::Group)
        {
            tmx::LayerGroup &layerGroup = mapLayer->getLayerAs<tmx::LayerGroup>();
            auto &layers = layerGroup.getLayers();
            vector<pair<Rectangle, Thing>> thingvector;
            int layercounter = -1;

            for(int i=0; i<layers.size(); i++)
            {
                if(layers[i]->getType() == tmx::Layer::Type::Object && layers[i]->getName() == "things")
                {
                    tmx::ObjectGroup &objectlayer = layers[i]->getLayerAs<tmx::ObjectGroup>();
                    auto &objects = objectlayer.getObjects();
                    for(auto &object : objects)
                    {
                        if(object.getShape() == tmx::Object::Shape::Rectangle)
                        {
                            Rectangle r(ceil(object.getAABB().left), 
                                ceil(object.getAABB().top), 
                                ceil(object.getAABB().width),
                                ceil(object.getAABB().height));
                            
                            Thing t = Thing();
                            t.setZ(r.getBottom());
                            thingvector.push_back(make_pair(r, t));

                            for(auto &prop : object.getProperties())
                            {
                                if(prop.getName() == "collision" and prop.getBoolValue() == true)
                                {
                                    this->_collisionRects.push_back(r);
                                }                            
                            }
                        }
                    }
                    for(auto &object : objects)
                    {
                        if(object.getShape() == tmx::Object::Shape::Point)
                        {
                            for(auto &p : thingvector)
                            {
                                if(utils::checkOverlap(p.first, xyfpair(object.getPosition().x, object.getPosition().y)))
                                {
                                    p.second.setZ(object.getPosition().y);
                                    break;
                                }
                            }
                        }
                    }
                    break;
                }
            }


            for(int i=0; i<layers.size(); i++)
            {
                if(layers[i]->getType() == tmx::Layer::Type::Tile)
                {
                    layercounter++;
                    tmx::TileLayer &tilelayer = layers[i]->getLayerAs<tmx::TileLayer>();
                    auto &tiles = tilelayer.getTiles();
                    int tileCounter=-1;

                    // for(auto &tile : tiles)
                    // {
                    //     tileCounter++;
                    //     xyfpair position = xyfpair((tileCounter%(int)this->_tileCount.x)*this->_mapTileSize.x, (tileCounter/(int)this->_tileCount.x)*this->_mapTileSize.y);
                    //     auto &tmxtile = tileData[tile.ID].tmxtile;
                    //     for(auto &rect : tileData[tile.ID].collisionRectObjects)
                    //     {
                    //         Rectangle r(position.x + rect.getLeft(), position.y + rect.getTop(), rect.getWidth(), rect.getHeight());
                    //         this->_collisionRects.push_back(r);
                    //     }
                    //     for(auto &rect : tileData[tile.ID].thingRectObjects)
                    //     {
                    //         Rectangle r(position.x + rect.getLeft(), position.y + rect.getTop(), rect.getWidth(), rect.getHeight());
                    //         Thing t = Thing();
                    //         t.setZ(rect.getBottom());
                    //         thingvector.push_back(make_pair(r, t));
                    //     }
                    // }

                    tileCounter = -1;
                    for(auto &tile : tiles)
                    {
                        tileCounter++;
                        if(tile.ID == 0)
                            continue;

                        // for(auto &tileset : tilesets)
                        // {
                        //     if(tileset.hasTile(tile.ID))
                        //     {
                                auto &tmxtileset = *tileData[tile.ID].tmxtileset;
                                auto &tmxtile = *tileData[tile.ID].tmxtile;
                                SDL_Surface *surface = this->_tilesets[tmxtileset.getFirstGID()].Surface;
                                xyipair tilesetPosition = xyipair(tmxtile.imagePosition.x, tmxtile.imagePosition.y);
                                xyfpair position = xyfpair((tileCounter%(int)this->_tileCount.x)*this->_mapTileSize.x, (tileCounter/(int)this->_tileCount.x)*this->_mapTileSize.y);
                                
                                position.y -= tmxtileset.getTileSize().y - this->_mapTileSize.h;
                                
                                if(this->_tileTextures.count(tile.ID) == 0)
                                    this->_tileTextures[tile.ID] = graphics.getTextureFromSurfaceRect(surface, tilesetPosition, xyipair(tmxtileset.getTileSize().x, tmxtileset.getTileSize().y));

                                Tile m_tile = Tile(this->_tileTextures[tile.ID], tile.ID, xyipair(tmxtileset.getTileSize().x, tmxtileset.getTileSize().y), xyipair(0,0), position);

                                for(auto &p : thingvector)
                                {
                                    if(utils::checkOverlap(p.first, m_tile))
                                    {
                                        m_tile.setZ(p.second.getZ() + 0.1*layercounter);
                                        p.second.addTile(m_tile);
                                        // p.second.setZ(p.second.getZ()+0.1*layercounter);
                                        goto TILE_ADDED;
                                    }
                                }

                                if(mapLayer->getName() == "background")
                                    m_tile.setZ(-100 + 0.1*layercounter);
                                else
                                    m_tile.setZ(position.y + tmxtileset.getTileSize().y);
                                this->_map.push_back(m_tile);
                                TILE_ADDED:;

                                // this->_map[bfground][tileCounter] = m_tile;
                                
                                // for(auto &object : tileset.getTile(tile.ID)->objectGroup.getObjects())
                                // {
                                //     Rectangle r(ceil(position.x + object.getAABB().left), 
                                //     ceil(position.y + object.getAABB().top), 
                                //     ceil(object.getAABB().width),
                                //     ceil(object.getAABB().height));
                                
                                //     this->_collisionRects.push_back(r);
                                // }
                                
                        //         break;
                        //     }
                        // }
                    }

                }

                for(auto &p : thingvector)
                {
                    if(!p.second.isEmpty())
                        this->_map.push_back(p.second);
                }

            }
        }

        else if(mapLayer->getType() == tmx::Layer::Type::Tile)
        {
            tmx::TileLayer &tilelayer = mapLayer->getLayerAs<tmx::TileLayer>();
                    
            auto &tiles = tilelayer.getTiles();
            int tileCounter=-1;
            for(auto &tile : tiles)
            {
                tileCounter++;
                if(tile.ID == 0)
                    continue;

                for(auto &tileset : tilesets)
                {
                    if(tileset.hasTile(tile.ID))
                    {
                        SDL_Surface *surface = this->_tilesets[tileset.getFirstGID()].Surface;
                        xyipair tilesetPosition = xyipair(tileset.getTile(tile.ID)->imagePosition.x, tileset.getTile(tile.ID)->imagePosition.y);
                        xyfpair position = xyfpair((tileCounter%(int)this->_tileCount.x)*this->_mapTileSize.x, (tileCounter/(int)this->_tileCount.x)*this->_mapTileSize.y);
                        
                        position.y -= tileset.getTileSize().y - this->_mapTileSize.h;
                        
                        if(this->_tileTextures.count(tile.ID) == 0)
                            this->_tileTextures[tile.ID] = graphics.getTextureFromSurfaceRect(surface, tilesetPosition, xyipair(tileset.getTileSize().x, tileset.getTileSize().y));

                        Tile m_tile = Tile(this->_tileTextures[tile.ID], tile.ID, xyipair(tileset.getTileSize().x, tileset.getTileSize().y), xyipair(0,0), position);

                        this->_map.push_back(m_tile);

                        // this->_map[bfground][tileCounter] = m_tile;
                        
                        // for(auto &object : tileset.getTile(tile.ID)->objectGroup.getObjects())
                        // {
                        //     Rectangle r(ceil(position.x + object.getAABB().left), 
                        //     ceil(position.y + object.getAABB().top), 
                        //     ceil(object.getAABB().width),
                        //     ceil(object.getAABB().height));
                        
                        //     this->_collisionRects.push_back(r);
                        // }
                        break;
                    }
                }
            }
        }

        // if layer is of objects
        else if(mapLayer->getType() == tmx::Layer::Type::Object)
        {
            tmx::ObjectGroup &objectlayer = mapLayer->getLayerAs<tmx::ObjectGroup>();

            if(objectlayer.getName() == "collision")
            {
                auto &objects = objectlayer.getObjects();
                for(auto &object : objects)
                {
                    if(object.getShape() == tmx::Object::Shape::Rectangle)
                    {
                        Rectangle r(ceil(object.getAABB().left), 
                            ceil(object.getAABB().top), 
                            ceil(object.getAABB().width),
                            ceil(object.getAABB().height));
                        
                        this->_collisionRects.push_back(r);
                    }
                    else if(object.getShape() == tmx::Object::Shape::Polyline ||
                            object.getShape() == tmx::Object::Shape::Polygon)
                    {
                        xyfpair linePos = xyfpair(object.getPosition().x, object.getPosition().y);
                        auto points = object.getPoints();
                        for(int i=0; i<(points.size()-((object.getShape() == tmx::Object::Shape::Polygon)? 0:1)) ; i++)
                        {
                            xyfpair lineStart = linePos + xyfpair(points[i].x, points[i].y);
                            xyfpair lineEnd = linePos + xyfpair(points[(i+1)%points.size()].x, points[(i+1)%points.size()].y);
                            this->_collisionSlopes.push_back(Line(lineStart, lineEnd));
                        }
                    }

                }
            }

            else if(objectlayer.getName() == "spawn_points")
            {
                auto &objects = objectlayer.getObjects();
                for(auto &object : objects)
                {
                    if(object.getName() == "player")
                    {
                        this->_playerSpawnPoint = xyipair(ceil(object.getPosition().x), 
                            ceil(object.getPosition().y));
                    }
                }
            }
        }
    }


}
