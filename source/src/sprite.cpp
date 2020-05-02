#include "sprite.h"
#include "graphics.h"
#include "globals.h"

Sprite::Sprite()
{
    this->SPRITE_DIR="content/sprites/";
}

Sprite::Sprite(Graphics &graphics, std::string filename, int sourceX, int sourceY, int w, int h, float posX, float posY)
{
    // Sprite();
    this->SPRITE_DIR="content/sprites/";

    this->_sourceRect.x=sourceX;
    this->_sourceRect.y=sourceY;
    this->_sourceRect.w=w;
    this->_sourceRect.h=h;

    this->_x=posX;
    this->_y=posY;

    std::string filepath=this->SPRITE_DIR+filename;
    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));
    if(this->_spriteSheet == NULL)  printf("Could not load the sprite");

}

void Sprite::draw(Graphics &graphics, int x, int y)
{
    SDL_Rect destRect = { x, y, this->_sourceRect.w * globals::SCALING, this->_sourceRect.h * globals::SCALING};
    graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destRect);
}

