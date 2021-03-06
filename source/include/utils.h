#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "tile.h"
#include "line.h"

namespace utils
{
    inline float distance(xyfpair &p, Line &l)
    {
        float dist = abs((l.p2.y-l.p1.y)*p.x - (l.p2.x-l.p1.x)*p.y + l.p2.x*l.p1.y - l.p2.y*l.p1.x) /
                        (sqrt((l.p2.y-l.p1.y)*(l.p2.y-l.p1.y) + (l.p2.x-l.p1.x)*(l.p2.x-l.p1.x)));
        return dist;
    }
    
    inline float distance(const xyfpair &p1, const xyfpair &p2)
    {
        float dist = sqrt((p2.y-p1.y)*(p2.y-p1.y) + (p2.x-p1.x)*(p2.x-p1.x));
        return dist;
    }







    inline bool checkOverlap(Rectangle &a, Rectangle &b)
    { 
        // If one rectangle is on left side of other 
        if (a.getTopLeft().x >= b.getBottomRight().x || b.getTopLeft().x >= a.getBottomRight().x) 
            return false; 
    
        // If one rectangle is above other 
        if (a.getTopLeft().y >= b.getBottomRight().y || b.getTopLeft().y >= a.getBottomRight().y) 
            return false; 
    
        return true; 
    }

    inline bool checkOverlap(const Rectangle &a, const Rectangle &b)
    { 
        // If one rectangle is on left side of other 
        if (a.getTopLeft().x >= b.getBottomRight().x || b.getTopLeft().x >= a.getBottomRight().x) 
            return false; 
    
        // If one rectangle is above other 
        if (a.getTopLeft().y >= b.getBottomRight().y || b.getTopLeft().y >= a.getBottomRight().y) 
            return false; 
    
        return true; 
    } 

    inline bool checkOverlap(Rectangle &a, Tile &b)
    { 
        Rectangle r = b.getRectangle();
        return checkOverlap(a, r);
    } 

    inline bool checkOverlap(SDL_Rect *a, SDL_Rect *b)
    {
        if(!a || !b)    return false;
        
        Rectangle ar = Rectangle(*a);
        Rectangle br = Rectangle(*b);
        return checkOverlap(ar, br);
    }

    inline bool checkOverlap(Rectangle &a, xyfpair b)
    { 
        return a.getLeft() <= b.x && 
               a.getRight() >= b.x &&
               a.getTop() <= b.y &&
               a.getBottom() >= b.y;
    } 


}

#endif