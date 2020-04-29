#include <SDL2/SDL.h>
#include "graphics.h"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(640, 480, 0, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Game");
}

Graphics::~Graphics()
{  
    SDL_DestroyWindow(this->_window);
}