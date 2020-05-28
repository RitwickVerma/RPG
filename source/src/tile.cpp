#include <SDL2/SDL.h>
#include "tile.h"
#include "graphics.h"
#include "renderable.h"
#include "rectangle.h"

Tile::Tile()
{
    this->_tileset=NULL;
    this->_size=xyipair(0,0);
    this->_tilesetPosition=xyipair(0,0);
    this->_position=xyfpair(0,0);
}

Tile::Tile(SDL_Texture *tileset, int ID, xyipair size, xyipair tilesetPosition, xyfpair position, float Z)
{
    this->_tileset=tileset;
    this->_ID=ID;
    this->_size=size;
    this->_tilesetPosition=tilesetPosition;
    this->_position=position;

    if(Z!=0)   this->z_comp = Z;
    else    this->z_comp = position.y + size.h;
}

void Tile::update(float elapsedTime)
{}


Rectangle Tile::getRectangle()
{ 
    return Rectangle(this->_position.x, this->_position.y, this->_size.h, this->_size.y);
}

void Tile::draw(Graphics &graphics)
{
    if(this->_tileset == NULL)  return;

    SDL_Rect sourceRect = { this->_tilesetPosition.x, this->_tilesetPosition.y, this->_size.x, this->_size.y};
    // SDL_Rect destRect = { (int)round(position.x), (int)round(position.y), this->_size.x , this->_size.y };
    SDL_Rect destRect = { (int)this->_position.x, (int)this->_position.y, this->_size.x , this->_size.y };
    
    Renderable r = Renderable(this->z_comp, this->_tileset, sourceRect, destRect);
    graphics.addToRenderQueue(r);
    // graphics.blitSurface(this->_tileset, &sourceRect, &destRect);
}