#ifndef LINE_H
#define LINE_H

#pragma once

#include "globals.h"
#include "rectangle.h"

class Line
{
    public:
        Line(){}
        Line(xyfpair pt1, xyfpair pt2):
            p1(pt1),
            p2(pt2)
        {
            if(this->p1.x != this->p2.x)
            {    
                this->m = (this->p1.y - this->p2.y)/(this->p1.x - this->p2.x);    
                this->b = this->p1.y - this->m * this->p1.x;
            }
            else
            {
                this->m=INT_MAX;
                this->b=INT_MAX;
            }
            
        }

        const inline float getSlope() const { return this->m; }
        const inline xyfpair getP1() const { return this->p1; }
        const inline xyfpair getP2() const { return this->p2; }

        bool pointsOnOppositeSide(xyfpair a, xyfpair b, xyfpair c, xyfpair d)
        {
            return (( ((a.y - b.y)*(c.x - a.x)  + 
                       (b.x - a.x)*(c.y - a.y)) *
                      ((a.y - b.y)*(d.x - a.x)  + 
                       (b.x - a.x)*(d.y - a.y)) ) < 0);
        }

        const vector<bool> getCollidingSides(const Rectangle &other) 
        {
            vector<bool> collidingSides(4, false);
            xyfpair a,b;
            vector<xyfpair> corners = other.getCorners();
            for(int i=0; i<corners.size(); i++)
            {
                a = corners[i];
                b = corners[(i+1)%corners.size()];
                bool side_collides = pointsOnOppositeSide(p1, p2, a, b);
                bool line_collides = pointsOnOppositeSide(a, b, p1, p2);
                if(line_collides && side_collides)
                    collidingSides[i] = true;
            }
            return collidingSides;
        }
        
        const bool collidesWith(const Rectangle &other)
        {
            vector<bool> collidingSides = getCollidingSides(other);
            return collidingSides[0] || collidingSides[1] ||
                   collidingSides[2] || collidingSides[3];
        }

        xyfpair p1, p2;
        float m, b;
};

#endif 