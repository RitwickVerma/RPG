#include <SDL2/SDL_image.h>

#include "graphics.h"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Game");
}

Graphics::~Graphics()
{  
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface * Graphics::loadImage(string &filepath)
{
    if(this->_spriteSheets.count(filepath) == 0)
        this->_spriteSheets[filepath] = IMG_Load(filepath.c_str());
    return this->_spriteSheets[filepath];
}

void Graphics::blitSurface(SDL_Texture *source, SDL_Rect *sourceRect, SDL_Rect *destRect) 
{
    // SDL_Rect tempdest = SDL_Rect(*destRect);
    SDL_RenderCopy(this->_renderer, source, sourceRect, destRect);        
}

void Graphics::flip()
{
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer *Graphics::getRenderer()
{
    return this->_renderer;
}
