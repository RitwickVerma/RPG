#include "level.h"
#include "graphics.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/Tileset.hpp>

Level::Level()
{
    MAP_DIR = "content/maps/";
}

Level::Level(Graphics &graphics, string mapName, xyipair spawnPoint, Rectangle *camera):Level()
{
    _mapName=mapName;
    _playerSpawnPoint=spawnPoint;
    _size=xyipair(0,0);
    _camera=camera;
    this->_hasGravity = false;

    this->loadMap(graphics, mapName); 
}

Level::~Level(){}

void Level::loadMap(Graphics &graphics, string mapName)
{
    string filepath=this->MAP_DIR+mapName;

    tmx::Map map;
    map.load(filepath);

    this->_tileSize = xyipair(map.getTileSize().x, map.getTileSize().y);
    this->_tileCount = xyipair(map.getTileCount().x, map.getTileCount().y);
    this->_size=xyipair(this->_tileCount * this->_tileSize);

    this->_map = vector<vector<Tile>>(2, vector<Tile>(this->_tileCount.y * this->_tileCount.x, Tile()));

    // Get all Tilesets and store them in the map _tilesets at key = firstGid
    for(auto &tileset : map.getTilesets())
    {
        string tilesetImagePath = tileset.getImagePath();
        SDL_Texture *tileset_texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(tilesetImagePath));
        this->_tilesets[tileset.getFirstGID()] = (Tileset(tileset_texture, tileset.getFirstGID()));
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
                        xyipair tilesetPosition = xyipair(tileset.getTile(tile.ID)->imagePosition.x, tileset.getTile(tile.ID)->imagePosition.y);
                        xyfpair position = xyfpair((tileCounter%(int)this->_tileCount.x)*this->_tileSize.x, (tileCounter/(int)this->_tileCount.x)*this->_tileSize.y);

                        Tile m_tile = Tile(this->_tilesets[tileset.getFirstGID()].Texture, tile.ID, this->_tileSize, tilesetPosition, position);

                        this->_map[bfground][tileCounter] = m_tile;

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
                    Rectangle r(ceil(object.getAABB().left), 
                        ceil(object.getAABB().top), 
                        ceil(object.getAABB().width),
                        ceil(object.getAABB().height));
                    r=r*globals::SCALING; 
                    this->_collisionRects.push_back(r);

                }
            }
            else if(objectlayer.getName() == "spawn_points")
            {
                auto &objects = objectlayer.getObjects();
                for(auto &object : objects)
                {
                    if(object.getName() == "player")
                    {
                        this->_playerSpawnPoint = xyipair(ceil(object.getAABB().left)*globals::SCALING, 
                            ceil(object.getAABB().top)*globals::SCALING);
                    }
                }
            }
        }
    }

}

void Level::update(float elapsedTime)
{ }

void Level::draw_background(Graphics &graphics)
{
    for(Tile &tile : this->_map[0])
    {   
        if(tile.getPosition().x > this->_camera->getLeft() - this->_tileSize.x && tile.getPosition().x + this->_tileSize.x < this->_camera->getRight() + this->_tileSize.x
            && tile.getPosition().y > this->_camera->getTop() - this->_tileSize.y && tile.getPosition().y + this->_tileSize.y < this->_camera->getBottom() + this->_tileSize.y)
            tile.draw(graphics, xyfpair(tile.getPosition().x - this->_camera->getLeft(), tile.getPosition().y - this->_camera->getTop()));
    }
}

void Level::draw_foreground(Graphics &graphics)
{
    for(Tile &tile : this->_map[1])
    {
        if(tile.getPosition().x > this->_camera->getLeft() - this->_tileSize.x && tile.getPosition().x + this->_tileSize.x < this->_camera->getRight() + this->_tileSize.x
            && tile.getPosition().y > this->_camera->getTop() - this->_tileSize.y && tile.getPosition().y + this->_tileSize.y < this->_camera->getBottom() + this->_tileSize.y)
            tile.draw(graphics, xyfpair(tile.getPosition().x - this->_camera->getLeft(), tile.getPosition().y - this->_camera->getTop()));
    }
}

vector<Rectangle> Level::checkTileCollision(const Rectangle &other)
{
    vector<Rectangle> collidingRects;
    for(auto &rectangle : this->_collisionRects)
    {
        if(rectangle.collidesWith(other))
            collidingRects.push_back(rectangle);
    }
    return collidingRects;
}

const xyipair Level::getPlayerSpawnPoint() const{
    return this->_playerSpawnPoint;
}