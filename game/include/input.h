#pragma once

#include "globals.h"

class input
{
public:
    input() = default;
    ~input() = default;

    // Non-copyable class
    input(const input&) = delete;
    input& operator=(input&) = delete;

protected:
    void begin_new_frame();
    void key_up_event(const SDL_Event& event);
    void key_down_event(const SDL_Event& event);

    bool was_key_pressed(SDL_Scancode key);
    bool was_key_released(SDL_Scancode key);
    bool is_key_held(SDL_Scancode key);

private:
    unordered_map<SDL_Scancode, bool> m_held_keys;
    unordered_map<SDL_Scancode, bool> m_pressed_keys;
    unordered_map<SDL_Scancode, bool> m_released_keys;
};

