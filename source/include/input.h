#ifndef INPUT_H
#define INPUT_H

#pragma once

#include "globals.h"

class Input
{
    public:
        void beginNewFrame();
        void keyUpEvent(const SDL_Event &event);
        void keyDownEvent(const SDL_Event &event);

        bool wasKeyPressed(SDL_Scancode key);
        bool wasKeyReleased(SDL_Scancode key);
        bool isKeyHeld(SDL_Scancode key);
    
    private:
        unordered_map<SDL_Scancode, bool> _heldKeys;
        unordered_map<SDL_Scancode, bool> _pressedKeys;
        unordered_map<SDL_Scancode, bool> _releasedKeys;

};

#endif