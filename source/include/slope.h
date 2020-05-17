#ifndef SLOPE_H
#define SLOPE_H

#pragma once

#include "globals.h"
#include "rectangle.h"

class Slope
{
    public:
        Slope(){}
        Slope(xyfpair p1, xyfpair p2):
            _p1(p1),
            _p2(p2)
        {
            if(this->_p1.x != this->_p2.x)
                this->_slope = (this->_p1.y - this->_p2.y)/(this->_p1.x - this->_p2.x);       
        }

        const inline float getSlope() const { return this->_slope; }
        const inline xyfpair getP1() const { return this->_p1; }
        const inline xyfpair getP2() const { return this->_p2; }

        const bool collidesWith(const Slope &other)
        {
            float uA = ((other.getP2().x-other.getP1().x)*(this->getP1().y-other.getP1().y) - 
                        (other.getP2().y-other.getP1().y)*(this->getP1().x-other.getP1().x)) / 
                       ((other.getP2().y-other.getP1().y)*(this->getP2().x-this->getP1().x) - 
                        (other.getP2().x-other.getP1().x)*(this->getP2().y-this->getP1().y));

            float uB = ((this->getP2().x-this->getP1().x)*(this->getP1().y-other.getP1().y) - 
                        (this->getP2().y-this->getP1().y)*(this->getP1().x-other.getP1().x)) / 
                       ((other.getP2().y-other.getP1().y)*(this->getP2().x-this->getP1().x) - 
                        (other.getP2().x-other.getP1().x)*(this->getP2().y-this->getP1().y));

            if (uA >= 0 && uA <= 1 && uB >= 0 && uB <= 1) {
                return true;
            }
            return false;
        }

        const bool collidesWith(const Rectangle &other)
        {
            // xyfpair normal = this->_p2 - this->_p1;
            // normal.swapXY();

            // xyfpair lineStart = this->_p1;
            // //we don't know yet on which side of the line the rectangle lies
            // float rectangleSide = 0;
            // for(xyfpair corner : other.getCorners())
            // {
            //     //cornerSide will be positive if the corner is on the side the normal points to,
            //     //zero if the corner is exactly on the line, and negative otherwise
            //     float cornerSide = normal.dot(corner - lineStart);
                
            //     if(rectangleSide == 0)
            //         //first evaluated corner or all previous corners lie exactly on the line
            //         rectangleSide = cornerSide;
            //     else
            //         if(cornerSide != 0 && //ignore corners on the line
            //         (cornerSide > 0) != (rectangleSide > 0)) //different sides
            //             return true; //rectangle intersects with line
            // }
            // return false;

            // return (other.getRight() >= this->_p2.x &&
			// 	other.getLeft() <= this->_p1.x &&
			// 	other.getTop() <= this->_p2.y &&
			// 	other.getBottom() >= this->_p1.y) ||
			// 	(other.getRight() >= this->_p1.x &&
			// 	other.getLeft() <= this->_p2.x &&
			// 	other.getTop() <= this->_p1.y &&
			// 	other.getBottom() >= this->_p2.y) ||
			// 	(other.getLeft() <= this->_p1.x &&
			// 	other.getRight() >= this->_p2.x &&
			// 	other.getTop() <= this->_p1.y &&
			// 	other.getBottom() >= this->_p2.y) ||
			// 	(other.getLeft() <= this->_p2.x &&
			// 	other.getRight() >= this->_p1.x &&
			// 	other.getTop() <= this->_p2.y &&
			// 	other.getBottom() >= this->_p1.y);

            bool left = this->collidesWith(Slope(other.getTopLeft(), other.getBottomLeft()));
            bool right = this->collidesWith(Slope(other.getTopRight(), other.getBottomRight()));
            bool top = this->collidesWith(Slope(other.getTopLeft(), other.getTopRight()));
            bool bottom = this->collidesWith(Slope(other.getBottomLeft(), other.getBottomRight()));

            if (left || right || top || bottom) {
                return true;
            }
            return false;
        }

    private:
        xyfpair _p1, _p2;
        float _slope;
};

#endif 