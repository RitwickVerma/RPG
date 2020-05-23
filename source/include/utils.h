#ifndef UTILS_H
#define UTILS_H

#pragma once

#include "globals.h"
#include "line.h"

namespace utils
{
    inline float distance(xyfpair p, Line l)
    {
        float dist = abs((l.p2.y-l.p1.y)*p.x - (l.p2.x-l.p1.x)*p.y + l.p2.x*l.p1.y - l.p2.y*l.p1.x) /
                        (sqrt((l.p2.y-l.p1.y)*(l.p2.y-l.p1.y) + (l.p2.x-l.p1.x)*(l.p2.x-l.p1.x)));
        return dist;
    }
    
    inline float distance(xyfpair p1, xyfpair p2)
    {
        float dist = sqrt((p2.y-p1.y)*(p2.y-p1.y) + (p2.x-p1.x)*(p2.x-p1.x));
        return dist;
    }
}

#endif