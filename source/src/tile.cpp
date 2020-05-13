#include <SDL2/SDL.h>
#include "tile.h"
#include "graphics.h"

Tile::Tile()
{
    this->_tileset=NULL;
    this->_size=xyipair(0,0);
    this->_tilesetPosition=xyipair(0,0);
    this->_position=xyfpair(0,0);
}

Tile::Tile(SDL_Texture *tileset, int ID, xyipair size, xyipair tilesetPosition, xyfpair position)
{
    this->_tileset=tileset;
    this->_ID=ID;
    this->_size=size;
    this->_tilesetPosition=tilesetPosition;
    this->_position=position;
}

void Tile::update(float elapsedTime)
{}

void Tile::draw(Graphics &graphics, xyfpair position)
{
    if(this->_tileset == NULL)  return;

    SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y};
    SDL_Rect destRect = { (int)round(position.x), (int)round(position.y), this->_size.x , this->_size.y };
    graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}