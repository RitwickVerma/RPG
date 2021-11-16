#ifndef SPRITE_H
#define SPRITE_H

#pragma once

#include "globals.h"
#include "rectangle.h"
#include "line.h"
#include "renderable.h"

struct Graphics;

class Sprite : public Renderable
{
public:
    Sprite();
    Sprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY);
    // virtual ~Sprite();
    virtual void update();
    void draw(Graphics &graphics, int x, int y);

    void bindSpritePositionTo(Sprite *);

    const Rectangle getBoundingBox() const;
    Rectangle getSpriteBox() { return this->_sprite; }
    const side::Side getCollisionSide(Rectangle &other) const;

    void setSpriteTexture(SDL_Texture *texture);

    void setX(float x) { this->_sprite.setLeft(x); }
    void setY(float y) { this->_sprite.setTop(y); }
    void setW(float w) { this->_sprite.setWidth(w); }
    void setH(float h) { this->_sprite.setHeight(h); }

    const float getX() const { return this->_sprite.getLeft(); }
    const float getY() const { return this->_sprite.getTop(); }
    const float getW() const { return this->_sprite.getWidth(); }
    const float getH() const { return this->_sprite.getHeight(); }
    SDL_Texture *getSpriteTexture() { return this->_spriteSheet; }

    bool isEmpty() { return this->SPRITE_NAME == ""; }

protected:
    SDL_Texture *_spriteSheet;
    Rectangle _boundingBox;
    Rectangle _sprite;

private:
    SDL_Rect _sourceRect;
    string SPRITE_DIR;
    string SPRITE_NAME;

    Sprite *_bindedSprite;
};

#endif // !SPRITE_H
