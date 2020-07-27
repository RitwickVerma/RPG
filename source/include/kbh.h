#ifndef KBH_H
#define KBH_H

#pragma once

#include "input.h"

struct Game;

class KeyboardHandler : protected Input
{
public:
    KeyboardHandler();
    void handle(Game &game);

private:
    void poll();
    SDL_Event event;
};

#endif // !KBH_H