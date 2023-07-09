#include "input.h"

void input::begin_new_frame()
{
    m_pressed_keys.clear();
    m_released_keys.clear();
}

void input::key_down_event(const SDL_Event& event)
{
    m_pressed_keys[event.key.keysym.scancode] = true;
    m_held_keys[event.key.keysym.scancode] = true;
}

void input::key_up_event(const SDL_Event& event)
{
    m_released_keys[event.key.keysym.scancode] = true;
    m_held_keys[event.key.keysym.scancode] = false;
}

bool input::was_key_pressed(SDL_Scancode key)
{
    try
    {
        return m_pressed_keys.at(key);
    }
    catch (out_of_range& out)
    {
        return false;
    }
}

bool input::was_key_released(SDL_Scancode key)
{
    try
    {
        return m_released_keys.at(key);
    }
    catch (out_of_range& out)
    {
        return false;
    }
}

bool input::is_key_held(SDL_Scancode key)
{
    try
    {
        return m_held_keys.at(key);
    }
    catch (out_of_range& out)
    {
        return false;
    }
}
