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

    // this->_boundingBox = Rectangle(this->_x, this->_y+this->_sourceRect.h*0.6, this->_sourceRect.w*globals::SCALING, this->_sourceRect.h*0.4*globals::SCALING);
    this->_boundingBox = Rectangle(this->_x, this->_y, this->_sourceRect.w*globals::SCALING, this->_sourceRect.h*globals::SCALING);

    this->_x=posX;
    this->_y=posY;

    string filepath=this->SPRITE_DIR+filename;
    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));
    if(this->_spriteSheet == NULL)  printf("Could not load the sprite");

}

void Sprite::update()
{
    // this->_boundingBox = Rectangle(this->_x, this->_y+this->_sourceRect.h*0.5, this->_sourceRect.w*globals::SCALING, this->_sourceRect.h*globals::SCALING);
    this->_boundingBox = Rectangle(this->_x, this->_y, this->_sourceRect.w*globals::SCALING, this->_sourceRect.h*globals::SCALING);
}

const Rectangle Sprite::getBoundingBox() const{
    return this->_boundingBox;
}

const sides::Side Sprite::getCollisionSide(Rectangle &other) const{
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = abs(this->_boundingBox.getRight() - other.getLeft());
    amtLeft = abs(this->_boundingBox.getLeft() - other.getRight());
    amtTop = abs(this->_boundingBox.getTop() - other.getBottom());
    amtBottom = abs(this->_boundingBox.getBottom() - other.getTop());

    int mini=min(amtRight, min(amtLeft, min(amtTop, amtBottom)));

    return 
        mini == amtRight ? sides::RIGHT :
        mini == amtLeft ? sides::LEFT :
        mini == amtTop ? sides::TOP :
        mini == amtBottom ? sides::BOTTOM :
        sides::NONE;
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
    SDL_Rect destRect = { x, y, this->_sourceRect.w * (int)globals::SCALING, this->_sourceRect.h * (int)globals::SCALING};
    graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &destRect);
}

