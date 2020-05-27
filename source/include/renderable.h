#ifndef RENDERABLE_H
#define RENDERABLE_H

#pragma once

#include "globals.h"

class Renderable
{
    public:
        Renderable(float Z, SDL_Texture *texture, SDL_Rect &sourceRect, SDL_Rect &destRect) :
            z_comp(Z),
            renderTexture(texture),
            renderSourceRect(sourceRect),
            renderDestRect(destRect)
        { }

        SDL_Texture *getTexture() const { return this->renderTexture; }
        SDL_Rect *getSourceRect() { return &this->renderSourceRect; }
        SDL_Rect *getDestRect() { return &this->renderDestRect; }
        float getZ() const { return this->z_comp; }


        void setTexture(SDL_Texture *texture) { this->renderTexture = texture; }
        void setSourceRect(SDL_Rect &sourceRect) { this->renderSourceRect = sourceRect; }
        void setDestRect(SDL_Rect &destRect) { this->renderDestRect = destRect; }
        void setZ(float z) { this->z_comp = z; }


    private:
        float z_comp;
        SDL_Texture *renderTexture;
        SDL_Rect renderSourceRect;
        SDL_Rect renderDestRect;

};

#endif // !RENDERABLE_H