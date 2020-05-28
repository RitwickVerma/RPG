#ifndef GLOBALS_H
#define GLOBALS_H

#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <variant>
#include <climits>
#include <SDL2/SDL.h>


using namespace std;
namespace globals
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    const float SCALING_X = 1;
    const float SCALING_Y = 1;
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

namespace corners{
    enum Corner
    { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, NONE };
}

enum Direction
{
    NORTH, SOUTH, EAST, WEST
};

struct xyipair
{
    int x,y,w,h;
    xyipair() { x=y=w=h=0; }
    xyipair(int x_pos, int y_pos)
    {
        x=w=x_pos;
        y=h=y_pos;
    }

    xyipair zero() { return xyipair(0,0); }

    xyipair operator*(const float &scale) { return xyipair(x*scale, y*scale); }

    xyipair operator*(const xyipair &temp) { return xyipair(x*temp.x, y*temp.y); }

    xyipair operator+(const xyipair &temp) { return xyipair(x+temp.x, y+temp.y); }
   
    xyipair operator-(const xyipair &temp) { return xyipair(x-temp.x, y-temp.y); }
    
    void swapXY() { swap(x ,y); }
};

struct xyfpair
{
    float x,y;
    xyfpair() { x=y=0.0; }
    xyfpair(float x_pos, float y_pos)
    {
        x=x_pos;
        y=y_pos;
    }

    xyfpair zero() { return xyfpair(0,0); }

    xyfpair operator*(const float &scale) { return xyfpair(x*scale, y*scale); }

    xyfpair operator*(const xyfpair &temp) { return xyfpair(x*temp.x, y*temp.y); }

    xyfpair operator+(const xyfpair &temp) { return xyfpair(x+temp.x, y+temp.y); }
    
    xyfpair operator-(const xyfpair &temp) { return xyfpair(x-temp.x, y-temp.y); }

    bool operator==(const xyfpair &temp) { return x==temp.x && y==temp.y; }

    bool operator!=(const xyfpair &temp) { return x!=temp.x && y!=temp.y; }

    float dot(const xyfpair &temp) { return this->x*temp.x + this->y*temp.y; }
    
    void swapXY() { swap(x ,y); }

};
#endif // !1 GLOBALS_H