#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <queue>
#include <string>
#include <variant>
#include <climits>
#include <memory>
#include <SDL2/SDL.h>

#include "xypair.h"

using namespace std;

namespace global
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    const float SCALING_X = 1;
    const float SCALING_Y = 1;
    inline bool DEV_MODE = false;
}

namespace side
{
    enum Side { TOP, BOTTOM, LEFT, RIGHT, NONE };
    inline Side getOppositeSide(Side side)
    {
        return 
            side == TOP ? BOTTOM:
            side == BOTTOM ? TOP:
            side == LEFT ? RIGHT:
            side == RIGHT ? LEFT:
            NONE;

    }
}

namespace corner{
    enum Corner { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, NONE };
}

namespace direction {
    enum Direction { NORTH, SOUTH, EAST, WEST };
}
namespace inv
{
    namespace weapon
    {
        enum Weapons { BASIC_BOW, BASIC_SWORD };
    }
}

#endif // !1 GLOBALS_H