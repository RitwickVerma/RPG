#include <SDL2/SDL.h>
#include "tile.h"
#include "graphics.h"

Tile::Tile()
{
    this->_tileset=NULL;
    this->_size=xypair(0,0);
    this->_tilesetPosition=xypair(0,0);
    this->_position=xypair(0,0);
}

Tile::Tile(SDL_Texture *tileset, xypair size, xypair tilesetPosition, xypair position)
{
    this->_tileset=tileset;
    this->_size=size;
    this->_tilesetPosition=tilesetPosition;
    this->_position=position*globals::SCALING;
}

void Tile::update(float elapsedTime)
{}

void Tile::draw(Graphics &graphics)
{
    if(this->_tileset == NULL)  return;
    
    SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y};
    SDL_Rect destRect = { this->_position.x, this->_position.y, this->_size.x * (int)globals::SCALING, this->_size.y * (int)globals::SCALING};
    graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}