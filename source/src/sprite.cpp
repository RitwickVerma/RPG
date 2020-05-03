#include "sprite.h"
#include "graphics.h"

Sprite::Sprite()
{
    this->SPRITE_DIR="content/sprites/";
}

Sprite::Sprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY)
{
    // Sprite();
    this->SPRITE_DIR="content/sprites/";

    this->_sourceRect.x=sourceX;
    this->_sourceRect.y=sourceY;
    this->_sourceRect.w=w;
    this->_sourceRect.h=h;

    // cout<<"in sprite "<<this->_sourceRect.w<<" "<<this->_sourceRect.h;

    this->_x=posX;
    this->_y=posY;

    string filepath=this->SPRITE_DIR+filename;
    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));
    if(this->_spriteSheet == NULL)  printf("Could not load the sprite");

}

void Sprite::update()
{

}

void Sprite::draw(Graphics &graphics, int x, int y)
{
    SDL_Rect destRect = { x, y, this->_sourceRect.w * (int)globals::SCALING, this->_sourceRect.h * (int)globals::SCALING};
    graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destRect);
}

