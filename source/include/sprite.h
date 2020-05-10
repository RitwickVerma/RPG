#ifndef SPRITE_H
#define SPRITE_H

#pragma once

#include "globals.h"
#include "rectangle.h"

struct Graphics;

class Sprite
{
    public:
        Sprite();
        Sprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY);
        // virtual ~Sprite();
        virtual void update();
        void draw(Graphics &graphics, int x, int y);

        const Rectangle getBoundingBox() const;
        const sides::Side getCollisionSide(Rectangle &other) const;

    protected:
        SDL_Rect _sourceRect, _destRect;
        SDL_Texture *_spriteSheet;
        float _x, _y; 
        Rectangle _boundingBox;

    private:
        string SPRITE_DIR;  
           
};


#endif // !SPRITE_H
