#include "level.h"
#include "graphics.h"
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>

Level::Level()
{
    MAP_DIR = "content/maps/";
}

Level::Level(Graphics &graphics, string mapName, xypair spawnPoint):Level()
{
    _mapName=mapName;
    _spawnPoint=spawnPoint;
    _size=xypair(0,0);

    this->loadMap(graphics, mapName); 
}

Level::~Level(){}

void Level::loadMap(Graphics &graphics, string mapName)
{
    string filepath=this->MAP_DIR+mapName;

    tmx::Map map;
    map.load(filepath);

    this->_tileSize = xypair(map.getTileSize().x, map.getTileSize().y);
    this->_tileCount = xypair(map.getTileCount().x, map.getTileCount().y);
    this->_size=xypair(this->_tileCount * this->_tileSize);

    this->_map = vector<Tile>(this->_tileCount.y * this->_tileCount.x, Tile());

    for(auto &tileset : map.getTilesets())
    {
        string tilesetImagePath = tileset.getImagePath();
        SDL_Texture *tileset_texture = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(tilesetImagePath));
        this->_tilesets[tileset.getFirstGID()] = (Tileset(tileset_texture, tileset.getFirstGID()));
    }

    auto &layers = map.getLayers();
    auto tilesets = map.getTilesets();
    for(auto &layer : layers)
    {
        if(!layer->getVisible())    continue; 
        if(layer->getType() == tmx::Layer::Type::Tile)
        {
            tmx::TileLayer &tilelayer = layer->getLayerAs<tmx::TileLayer>();

            auto tiles = tilelayer.getTiles();
            int tileCounter=-1;
            for(auto tile : tiles)
            {
                tileCounter++;
                if(tile.ID == 0)
                    continue;

                for(auto &tileset : tilesets)
                {
                    if(tileset.hasTile(tile.ID))
                    {
                        xypair tilesetPosition = xypair(tileset.getTile(tile.ID)->imagePosition.x, tileset.getTile(tile.ID)->imagePosition.y);
                        xypair position = xypair((tileCounter%this->_tileCount.x)*this->_tileSize.x, (tileCounter/this->_tileCount.x)*this->_tileSize.y);

                        Tile m_tile = Tile(this->_tilesets[tileset.getFirstGID()].Texture, this->_tileSize, tilesetPosition, position);

                        this->_map[tileCounter] = m_tile;

                        break;
                    }
                }
            }
        }
    }

    // this->_backgroundTexture=SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));
}

void Level::update(float elapsedTime)
{

}

void Level::draw(Graphics &graphics)
{
    for(Tile tile : this->_map)
    {
        tile.draw(graphics);
    }
}