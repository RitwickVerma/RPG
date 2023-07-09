#pragma once

#include "input.h"

struct Game;

class keyboard_handler : protected input
{
public:
    keyboard_handler() : m_event()
    {
    }

    ~keyboard_handler() = default;

    // Non-copyable class
    keyboard_handler(const keyboard_handler&) = delete;
    keyboard_handler& operator=(keyboard_handler&) = delete;

    void handle(Game& game);

private:
    void poll();
    SDL_Event m_event;
};
