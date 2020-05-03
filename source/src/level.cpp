#include "level.h"
#include "graphics.h"

Level::Level(){}

Level::Level(Graphics &graphics, string mapName, vector2 spawnPoint)
{
    _mapName=mapName;
    _spawnPoint=spawnPoint;
    _size=vector2(0,0);

    this->loadMap(graphics, mapName); 
}

Level::~Level(){}

void Level::loadMap(Graphics &graphics, string mapName)
{
    string filepath="content/backgrounds/grass2.png";
    this->_backgroundTexture=SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));
    
    this->_size=vector2(1920, 1080);
}

void Level::update(float elapsedTime)
{

}

void Level::draw(Graphics &graphics)
{
    SDL_Rect sourceRect = {0, 0, 32, 32};
    SDL_Rect destRect;
    for(int i=0; i< this->_size.x; i+=32)
    {
        for(int j=0; j<this->_size.y; j+=32)
        {
            destRect.x=i;
            destRect.y=j;
            destRect.w=32;
            destRect.h=32;
            graphics.blitSurface(this->_backgroundTexture, &sourceRect, &destRect);
        }
    }
}