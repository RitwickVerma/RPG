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
    this->_position=position*globals::SCALING;
}

void Tile::addOffset(xyfpair offset)
{
    this->_position.x+=offset.x;
    this->_position.y+=offset.y;
}

void Tile::update(float elapsedTime)
{}

void Tile::draw(Graphics &graphics)
{
    if(this->_tileset == NULL)  return;

    // if(this->_ID==1)    cout<<this->_position.x<<endl;

    // this->_position.x=float(int(this->_position.x));
    // this->_position.y=float(int(this->_position.y));
    SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y};
    SDL_Rect destRect = { round(this->_position.x), round(this->_position.y), this->_size.x * (int)globals::SCALING, this->_size.y * (int)globals::SCALING};
    graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}