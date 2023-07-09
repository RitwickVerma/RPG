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
    Renderable() {}

    void makeRenderable(float Z, SDL_Texture *texture, SDL_Rect &sourceRect, SDL_Rect &destRect, string type = "", int opacity = 100)
    {
        this->z_comp = Z;
        this->renderTexture = texture;
        this->renderSourceRect = sourceRect;
        this->renderDestRect = destRect;
        this->renderOpacity = opacity;
        this->renderType = type;
    }

    SDL_Texture *getRenderableTexture() const { return this->renderTexture; }
    SDL_Rect *getRenderableSourceRect() { return &this->renderSourceRect; }
    SDL_Rect *getRenderableDestRect() { return &this->renderDestRect; }
    float getRenderableZ() const { return this->z_comp; }
    string getRenderableType() const { return this->renderType; }

    void setRenderableTexture(SDL_Texture *texture) { this->renderTexture = texture; }
    void setRenderableSourceRect(SDL_Rect &sourceRect) { this->renderSourceRect = sourceRect; }
    void setRenderableDestRect(SDL_Rect &destRect) { this->renderDestRect = destRect; }
    void setRenderableZ(float z) { this->z_comp = z; }
    void setRenderableType(string renderableType) { this->renderType = renderableType; }

private:
    float z_comp;
    string renderType;
    int renderOpacity;
    SDL_Texture *renderTexture;
    SDL_Rect renderSourceRect;
    SDL_Rect renderDestRect;
};

#endif