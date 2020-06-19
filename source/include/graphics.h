#ifndef GRAPHICS_H
#define GRAPHICS_H

#pragma once

#include "globals.h"
#include "renderable.h"
#include "rectangle.h"

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

        void addToRenderQueue(Renderable renderable);

        void drawQueue();

        /* Updates the screen with rendering performed since previous call */
        void flip();
        
        /* Clear Rendering Target */
        void clear(); 

        /* Returns instance of Renderer */
        SDL_Renderer *getRenderer();

        void fadeToBlack();
        
        void fadeFromBlack();

        Rectangle *getCamera();


        struct sort_by_z
        {
            bool operator()(Renderable &a, Renderable &b) 
            {
                if(a.getZ() == b.getZ())
                    return a.getDestRect()->x > b.getDestRect()->x;
                return a.getZ() > b.getZ(); 
            }
        };

    private:
        SDL_Window  *_window;
        SDL_Renderer *_renderer;
        Rectangle _camera;

        priority_queue< Renderable, vector<Renderable>, sort_by_z > _render_queue;
        std::map<std::string, SDL_Surface*> _spriteSheets;
};



#endif