#ifndef GLOBALS_H
#define GLOBALS_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>

#pragma once

using namespace std;
namespace globals
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    const float SCALING = 1;
    // const string SPRITE_DIR = "/content/sprite/";

}

namespace sides
{
    enum Side
    {
        TOP, BOTTOM, LEFT, RIGHT, NONE
    };
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

enum Direction
{
    NORTH, SOUTH, EAST, WEST
};

struct xyipair
{
    int x,y;
    xyipair()
    {
        x=y=0;
    }
    xyipair(int x_pos, int y_pos)
    {
        x=x_pos;
        y=y_pos;
    }
    xyipair zero()
    {
        return xyipair(0,0);
    }

    xyipair operator*(const float &scale)
    {
        return xyipair(x*scale, y*scale);
    }

    xyipair operator*(const xyipair &temp)
    {
        return xyipair(x*temp.x, y*temp.y);
    }

    xyipair operator+(const xyipair &temp)
    {
        return xyipair(x+temp.x, y+temp.y);
    }
    // xyipair operator=(const xyfpair &temp)
    // {
    //     return xyipair(temp.x, temp.y);
    // }
};

struct xyfpair
{
    float x,y;
    xyfpair()
    {
        x=y=0.0;
    }
    xyfpair(float x_pos, float y_pos)
    {
        x=x_pos;
        y=y_pos;
    }
    xyfpair zero()
    {
        return xyfpair(0,0);
    }

    xyfpair operator*(const float &scale)
    {
        return xyfpair(x*scale, y*scale);
    }

    xyfpair operator*(const xyipair &temp)
    {
        return xyfpair(x*temp.x, y*temp.y);
    }

    xyfpair operator+(const xyipair &temp)
    {
        return xyfpair(x+temp.x, y+temp.y);
    }

};
#endif // !1 GLOBALS_H