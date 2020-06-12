#ifndef RENDERABLE_H
#define RENDERABLE_H

#pragma once


struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;


class Renderable
{
    public:
        Renderable(float Z, SDL_Texture *texture, SDL_Rect &sourceRect, SDL_Rect &destRect, string renderableType = "") :
            z_comp(Z),
            renderTexture(texture),
            renderSourceRect(sourceRect),
            renderDestRect(destRect),
            type(renderableType)
        { }

        SDL_Texture *getTexture() const { return this->renderTexture; }
        SDL_Rect *getSourceRect() { return &this->renderSourceRect; }
        SDL_Rect *getDestRect() { return &this->renderDestRect; }
        float getZ() const { return this->z_comp; }
        string getType() const { return this->type; }


        void setTexture(SDL_Texture *texture) { this->renderTexture = texture; }
        void setSourceRect(SDL_Rect &sourceRect) { this->renderSourceRect = sourceRect; }
        void setDestRect(SDL_Rect &destRect) { this->renderDestRect = destRect; }
        void setZ(float z) { this->z_comp = z; }
        void setType(string renderableType) { this->type = renderableType; }


    private:
        float z_comp;
        string type;
        SDL_Texture *renderTexture;
        SDL_Rect renderSourceRect;
        SDL_Rect renderDestRect;

};

#endif