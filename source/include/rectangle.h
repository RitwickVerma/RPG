#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once

#include "globals.h"

class Rectangle
{
    public:
        Rectangle(){}

        Rectangle(int x, int y, int width, int height):
            _x(x),
            _y(y),
            _width(width),
            _height(height)
        {}
        Rectangle(SDL_Rect r):
            _x(r.x),
            _y(r.y),
            _width(r.w),
            _height(r.h)
        {}

        Rectangle operator*(const float &scale) { return Rectangle(_x*scale, _y*scale, _width*scale, _height*scale); }

        const float getCenterX() const { return this->_x + this->_width/2; }
        const float getCenterY() const { return this->_y + this->_height/2; }
        const xyfpair getCenter() const { return xyfpair(this->getCenterX(), this->getCenterY()); }

        const float getLeft() const { return this->_x; }
        const float getRight() const { return this->_x + this->_width; }
        const float getTop() const { return this->_y; }
        const float getBottom() const { return this->_y + this->_height; }
        

        const float getWidth() const { return this->_width; }
        const float getHeight() const { return this->_height; }

        const int getSide(const sides::Side side) const {
            return 
                side == sides::LEFT ? this->getLeft():
                side == sides::RIGHT ? this->getRight():
                side == sides::TOP ? this->getTop():
                side == sides::BOTTOM ? this->getBottom():
                sides::NONE;
        }

        void setCenterX(float x) { this->_x = x - this->_width/2; }
        void setCenterY(float y) { this->_y = y - this->_height/2; }
        void setCenter(float x, float y) { this->setCenterX(x); this->setCenterY(y); } 
        void setCenter(xyfpair xy) { this->setCenterX(xy.x); this->setCenterY(xy.y); } 
        
        void setLeft(float x) { this->_x = x; }
        void setRight(float x) { this->_x = x - this->_width; }
        void setTop(float y) { this->_y = y; }
        void setBottom(float y) { this->_y = y - this->_height; }

        /* Checks collision with argument Rectangle */
        const bool collidesWith(const Rectangle &other) const{
            return 
                this->getRight() >= other.getLeft() &&
                this->getLeft() <= other.getRight() &&
                this->getTop() <= other.getBottom() &&
                this->getBottom() >= other.getTop();
        }
        const bool containedWithin(const Rectangle &other) const{
            return 
                this->getLeft() > other.getLeft() &&
                this->getRight()< other.getRight() &&
                this->getTop() > other.getTop() &&
                this->getBottom() < other.getBottom();
        }

        /* checks is a Rectangle is valid */
        const bool isValidRect() const 
        {
            return this->_x>=0 && this->_y>=0 && this->_width>=0 && this->_height>=0;
        }

    private:
        float _x, _y, _height, _width;
};

#endif // !RECTANGLE_H