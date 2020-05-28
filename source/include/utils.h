#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "tile.h"

namespace utils
{
    inline float distance(xyfpair &p, Line &l)
    {
        float dist = abs((l.p2.y-l.p1.y)*p.x - (l.p2.x-l.p1.x)*p.y + l.p2.x*l.p1.y - l.p2.y*l.p1.x) /
                        (sqrt((l.p2.y-l.p1.y)*(l.p2.y-l.p1.y) + (l.p2.x-l.p1.x)*(l.p2.x-l.p1.x)));
        return dist;
    }
    
    inline float distance(xyfpair &p1, xyfpair &p2)
    {
        float dist = sqrt((p2.y-p1.y)*(p2.y-p1.y) + (p2.x-p1.x)*(p2.x-p1.x));
        return dist;
    }

    bool checkOverlap(Rectangle &a, Rectangle &b)
    { 
        // If one rectangle is on left side of other 
        if (a.getTopLeft().x >= b.getBottomRight().x || b.getTopLeft().x >= a.getBottomRight().x) 
            return false; 
    
        // If one rectangle is above other 
        if (a.getTopLeft().y >= b.getBottomRight().y || b.getTopLeft().y >= a.getBottomRight().y) 
            return false; 
    
        return true; 
    } 

    bool checkOverlap(Rectangle &a, Tile &b)
    { 
        Rectangle r = b.getRectangle();
        return checkOverlap(a, r);
    } 

    bool checkOverlap(Rectangle &a, xyfpair b)
    { 
        return a.getLeft() <= b.x && 
               a.getRight() >= b.x &&
               a.getTop() <= b.y &&
               a.getBottom() >= b.y;
    } 

}

#endif