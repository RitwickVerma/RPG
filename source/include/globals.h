#ifndef GLOBALS_H
#define GLOBALS_H

#include <bits/stdc++.h>

using namespace std;
namespace globals
{
    const int SCREEN_WIDTH = 1920;
    const int SCREEN_HEIGHT = 1080;
    const float SCALING = 1;
    // const string SPRITE_DIR = "/content/sprite/";

}

struct vector2
{
    int x,y;
    vector2()
    {
        x=y=0;
    }
    vector2(int x_pos, int y_pos)
    {
        x=x_pos;
        y=y_pos;
    }
    vector2 zero()
    {
        return vector2(0,0);
    }

};

#endif // !1 GLOBALS_H