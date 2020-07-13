#include "sprite.h"
#include "graphics.h"

Sprite::Sprite()
{
    this->SPRITE_DIR="content/sprites/";
}

Sprite::Sprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY) 
{
    this->SPRITE_DIR = "content/sprites/";
    this->SPRITE_NAME = filename;

    this->_sourceRect.x = sourceX;
    this->_sourceRect.y = sourceY;
    this->_sourceRect.w = w;
    this->_sourceRect.h = h;

    this->_sprite = Rectangle(posX, posY, w, h);

    this->_boundingBox = this->_sprite;
    this->_bindedSprite = NULL;

    string filepath = this->SPRITE_DIR+filename;
    this->_spriteSheet = SDL_CreateTextureFromSurface(graphics.getRenderer(), graphics.loadImage(filepath));
    if(this->_spriteSheet == NULL)  printf("Could not load the sprite");

}

void Sprite::setSpriteTexture(SDL_Texture *texture)
{
    this->_spriteSheet = texture;
}

const Rectangle Sprite::getBoundingBox() const{
    return this->_boundingBox;
}

void Sprite::bindSpritePositionTo(Sprite *sprite)
{
    this->_bindedSprite = sprite;
}

const side::Side Sprite::getCollisionSide(Rectangle &other) const{
    int amtRight, amtLeft, amtTop, amtBottom;
    amtRight = abs(this->_boundingBox.getRight() - other.getLeft());
    amtLeft = abs(this->_boundingBox.getLeft() - other.getRight());
    amtTop = abs(this->_boundingBox.getTop() - other.getBottom());
    amtBottom = abs(this->_boundingBox.getBottom() - other.getTop());

    int mini=min(amtRight, min(amtLeft, min(amtTop, amtBottom)));

    return
        mini == amtRight ? side::RIGHT :
        mini == amtLeft ? side::LEFT :
        mini == amtTop ? side::TOP :
        mini == amtBottom ? side::BOTTOM :
        side::NONE;
}

void Sprite::update()
{ 
    if(this->_bindedSprite != NULL)
    {
        this->_sprite.x() = this->_bindedSprite->getX();
        this->_sprite.y() = this->_bindedSprite->getY();
    }
}

void Sprite::draw(Graphics &graphics, int x, int y)
{
    SDL_Rect _destRect = { x, y, this->_sourceRect.w , this->_sourceRect.h };
    graphics.blitSurface(this->_spriteSheet, &this->_sourceRect, &_destRect);
}

