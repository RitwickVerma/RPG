#ifndef RENDERABLE_H
#define RENDERABLE_H

#pragma once

#include "globals.h"

class Renderable
{
    protected:

    SDL_Texture *texture;
    SDL_Rect *sourceRect;
    SDL_Rect *destRect;
};

#endif // !RENDERABLE_H