#include <SDL2/SDL_image.h>

#include "graphics.h"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Game");
    SDL_RenderSetScale(this->_renderer, globals::SCALING_X, globals::SCALING_Y);
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

SDL_Surface *Graphics::getSurfaceFromRect(SDL_Surface *surface, xyipair pos, xyipair size)
{
    SDL_LockSurface(surface);
    surface->userdata = (void*)((unsigned*)surface->pixels + pos.y*surface->w + pos.x);
    SDL_UnlockSurface(surface);
    SDL_Surface *newSurface = SDL_CreateRGBSurfaceWithFormatFrom(surface->userdata, size.x, size.y, surface->format->BitsPerPixel, surface->pitch, surface->format->format);
    return newSurface;
}

SDL_Texture* Graphics::getTextureFromSurfaceRect(SDL_Surface *surface, xyipair pos, xyipair size)
{
    SDL_Surface *newSurface = this->getSurfaceFromRect(surface, pos, size);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, newSurface);
    return texture;
}

void Graphics::addToRenderQueue(Renderable renderable)
{
    this->_render_queue.push(renderable);
}

void Graphics::drawQueue()
{
    while(!this->_render_queue.empty())
    {   
        auto renderable = this->_render_queue.top();
        this->blitSurface(renderable.getTexture(), renderable.getSourceRect(), renderable.getDestRect());
        this->_render_queue.pop();
    }
}

void Graphics::blitSurface(SDL_Texture *source, SDL_Rect *sourceRect, SDL_Rect *destRect) 
{
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
