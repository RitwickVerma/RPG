#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once

#include "globals.h"
#include "utils.h"
class Rectangle
{
    public:
        Rectangle(){} 

        Rectangle(int x, int y, int width, int height):
            _x(x),
            _y(y),
            _w(width),
            _h(height)
        {}
        Rectangle(SDL_Rect r):
            _x(r.x),
            _y(r.y),
            _w(r.w),
            _h(r.h)
        {}

        Rectangle operator*(const float &scale) { return Rectangle(_x*scale, _y*scale, _w*scale, _h*scale); }

        void update(int x, int y, int width, int height)
        {
                this->_x = x;
                this->_y = y;
                this->_w = width;
                this->_h = height;
        }


        float & x() { return this->_x; }
        float & y() { return this->_y; }
        float & w() { return this->_w; }
        float & h() { return this->_h; }


        const float getCenterX() const { return this->_x + this->_w/2; }
        const float getCenterY() const { return this->_y + this->_h/2; }
        const xyfpair getCenter() const { return xyfpair(this->getCenterX(), this->getCenterY()); }

        const float getLeft() const { return this->_x; }
        const float getRight() const { return this->_x + this->_w; }
        const float getTop() const { return this->_y; }
        const float getBottom() const { return this->_y + this->_h; }

        const xyfpair getTopLeft() const { return xyfpair(this->getLeft(), this->getTop()); }
        const xyfpair getTopRight() const { return xyfpair(this->getRight(), this->getTop()); }
        const xyfpair getBottomLeft() const { return xyfpair(this->getLeft(), this->getBottom()); }
        const xyfpair getBottomRight() const { return xyfpair(this->getRight(), this->getBottom()); }
        

        const float getWidth() const { return this->_w; }
        const float getHeight() const { return this->_h; }

        const int getSide(const sides::Side side) const {
            return 
                side == sides::LEFT ? this->getLeft():
                side == sides::RIGHT ? this->getRight():
                side == sides::TOP ? this->getTop():
                side == sides::BOTTOM ? this->getBottom():
                sides::NONE;
        }

        const Rectangle getRectangle() { return *this; }
        
        const vector<xyfpair> getCorners() const
        {
            vector<xyfpair> corners;
            corners.push_back(this->getTopLeft());
            corners.push_back(this->getTopRight());
            corners.push_back(this->getBottomRight());
            corners.push_back(this->getBottomLeft());
            return corners;
        }

        void setCenterX(float x) { this->_x = x - this->_w/2; }
        void setCenterY(float y) { this->_y = y - this->_h/2; }
        void setCenter(float x, float y) { this->setCenterX(x); this->setCenterY(y); } 
        void setCenter(xyfpair xy) { this->setCenterX(xy.x); this->setCenterY(xy.y); } 
        
        void setLeft(float x) { this->_x = x; }
        void setRight(float x) { this->_x = x - this->_w; }
        void setTop(float y) { this->_y = y; }
        void setBottom(float y) { this->_y = y - this->_h; }

        /* Checks collision with argument Rectangle */
        const bool collidesWith(const Rectangle &other) const {
            return
                this->getRight() >= other.getLeft() &&
                this->getLeft() <= other.getRight() &&
                this->getTop() <= other.getBottom() &&
                this->getBottom() >= other.getTop();
        }

        const bool containedWithin(const Rectangle &other) const{
            return 
                this->getLeft() > other.getLeft() &&
                this->getRight() < other.getRight() &&
                this->getTop() > other.getTop() &&
                this->getBottom() < other.getBottom();
        }

        void containWithin(const Rectangle &other) {
            if(containedWithin(other))
                return;
            
            if(getLeft()<other.getLeft())       setLeft(other.getLeft());
            if(getRight()>other.getRight())     setRight(other.getRight());
            if(getTop()<other.getTop())         setTop(other.getTop());
            if(getBottom()>other.getBottom())   setBottom(other.getBottom());

            
            // if(!containedWithin(other)) setCenter(other.getCenter());
        }

        /* checks is a Rectangle is valid */
        const bool isValidRect() const 
        {
            return this->_x>=0 && this->_y>=0 && this->_w>=0 && this->_h>=0;
        }

    private:
        float _x, _y, _h, _w;

};

#endif // !RECTANGLE_H