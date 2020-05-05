#ifndef GLOBALS_H
#define GLOBALS_H

#include <bits/stdc++.h>
#include <SDL2/SDL.h>

using namespace std;
namespace globals
{
    const int SCREEN_WIDTH = 1280;
    const int SCREEN_HEIGHT = 720;
    const float SCALING = 1;
    // const string SPRITE_DIR = "/content/sprite/";

}

enum Direction
{
    NORTH, SOUTH, EAST, WEST
};
struct xypair
{
    int x,y;
    xypair()
    {
        x=y=0;
    }
    xypair(int x_pos, int y_pos)
    {
        x=x_pos;
        y=y_pos;
    }
    xypair zero()
    {
        return xypair(0,0);
    }

    xypair operator*(const float &scale)
    {
        return xypair(x*scale, y*scale);
    }

    xypair operator*(const xypair &temp)
    {
        return xypair(x*temp.x, y*temp.y);
    }

    xypair operator+(const xypair &temp)
    {
        return xypair(x+temp.x, y+temp.y);
    }

};

#endif // !1 GLOBALS_H