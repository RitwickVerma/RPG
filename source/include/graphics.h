#ifndef GRAPHICS_H
#define GRAPHICS_H

#pragma once

#include "globals.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;
struct SDL_Rect;

class Graphics
{
    public:
        Graphics();
        ~Graphics();

        SDL_Surface *loadImage(string &filename);

        /* Renders sourceRect from texture source to destRect on rendering target (window) */
        void blitSurface(SDL_Texture *source, SDL_Rect *sourceRect, SDL_Rect *destRect);
        
        /* Returns part of a surface from a bigger surface */
        SDL_Surface* getSurfaceFromRect(SDL_Surface *surface, xyipair pos, xyipair size);
        
        /* Returns a texture from part of a surface (calls getSurfaceFromRect) */
        SDL_Texture* getTextureFromSurfaceRect(SDL_Surface *surface, xyipair pos, xyipair size);

        /* Updates the screen with rendering performed since previous call */
        void flip();
        
        /* Clear Rendering Target */
        void clear(); 

        /* Returns instance of Renderer */
        SDL_Renderer *getRenderer();

    private:
        SDL_Window  *_window;
        SDL_Renderer *_renderer;

        std::map<std::string, SDL_Surface*> _spriteSheets;
};


#endif