#ifndef SPRITE_H
#define SPRITE_H

#pragma once

#include "globals.h"
#include "rectangle.h"
#include "line.h"
#include "renderable.h"
// #include "utils.h"

struct Graphics;

class Sprite : public Renderable
{
    public:
        Sprite();
        Sprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY);
        // virtual ~Sprite();
        virtual void update();
        void draw(Graphics &graphics, int x, int y);

        const Rectangle getBoundingBox() const;
        const sides::Side getCollisionSide(Rectangle &other) const;

        const float getX() const { return this->_sprite.x; }
        const float getY() const { return this->_sprite.y; }
        const float getW() const { return this->_sprite.w; }
        const float getH() const { return this->_sprite.h; }
        
    protected:
        SDL_Texture *_spriteSheet;
        // float x, y; 
        Rectangle _boundingBox;
        Rectangle _sprite;
        // xyipair _size;

    private:
        SDL_Rect _sourceRect ;
        string SPRITE_DIR;  
           
};


#endif // !SPRITE_H
