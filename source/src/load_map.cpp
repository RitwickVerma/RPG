#include "level.h"
#include "graphics.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Tileset.hpp>

void Level::loadMap(Graphics &graphics, string mapName)
{
    string filepath=this->MAP_DIR+mapName;

    tmx::Map map;
    map.load(filepath);

    this->_mapTileSize = xyipair(map.getTileSize().x, map.getTileSize().y);
    this->_tileCount = xyipair(map.getTileCount().x, map.getTileCount().y);
    this->_size=xyipair(this->_tileCount * this->_mapTileSize);

    this->_map = vector<vector<Tile>>(2, vector<Tile>(this->_tileCount.y * this->_tileCount.x, Tile()));

    // Get all Tilesets and store them in the map _tilesets at key = firstGid
    for(auto &tileset : map.getTilesets())
    {
        string tilesetImagePath = tileset.getImagePath();
        // SDL_Texture *tileset_texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(tilesetImagePath));
        // if(tileset_texture == NULL)
        // {
        //     SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Could not create texture from surface");
        //     cout<<SDL_GetError();
        // }
        this->_tilesets[tileset.getFirstGID()] = (Tileset(graphics.loadImage(tilesetImagePath), tileset.getFirstGID()));
    }


    // Get all Layers and process them one by one
    auto &layers = map.getLayers();
    auto &tilesets = map.getTilesets();
    for(auto &layer : layers)
    {
        // Ignore layers that aren't visible
        if(!layer->getVisible())    continue; 

        // if layer is of tiles
        if(layer->getType() == tmx::Layer::Type::Tile)
        {
            tmx::TileLayer &tilelayer = layer->getLayerAs<tmx::TileLayer>();

            int bfground=0;
            if(tilelayer.getName() == "foreground") bfground=1;

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
                        // xyipair tilesetPosition = xyipair(0,0);
                        xyfpair position = xyfpair((tileCounter%(int)this->_tileCount.x)*this->_mapTileSize.x, (tileCounter/(int)this->_tileCount.x)*this->_mapTileSize.y);
                        position.y -= tileset.getTileSize().y - this->_mapTileSize.h;
                        if(this->_tileTextures.count(tile.ID) == 0)
                            this->_tileTextures[tile.ID] = graphics.getTextureFromSurfaceRect(surface, tilesetPosition, xyipair(tileset.getTileSize().x, tileset.getTileSize().y));

                        Tile m_tile = Tile(this->_tileTextures[tile.ID], tile.ID, xyipair(tileset.getTileSize().x, tileset.getTileSize().y), xyipair(0,0), position);

                        this->_map[bfground][tileCounter] = m_tile;
                        
                        for(auto &object : tileset.getTile(tile.ID)->objectGroup.getObjects())
                        {
                            Rectangle r(ceil(position.x + object.getAABB().left), 
                            ceil(position.y + object.getAABB().top), 
                            ceil(object.getAABB().width),
                            ceil(object.getAABB().height));
                        
                            this->_collisionRects.push_back(r);
                        }
                        break;
                    }
                }
            }
        }

        // if layer is of objects
        else if(layer->getType() == tmx::Layer::Type::Object)
        {
            tmx::ObjectGroup &objectlayer = layer->getLayerAs<tmx::ObjectGroup>();

            if(objectlayer.getName() == "collisions")
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
