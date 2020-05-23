#ifndef RECTANGLE_H
#define RECTANGLE_H

#pragma once

#include "globals.h"

class Rectangle
{
    public:
        Rectangle(){} 

        Rectangle(int x, int y, int width, int height):
            x(x),
            y(y),
            w(width),
            h(height)
        {}
        Rectangle(SDL_Rect r):
            x(r.x),
            y(r.y),
            w(r.w),
            h(r.h)
        {}

        Rectangle operator*(const float &scale) { return Rectangle(x*scale, y*scale, w*scale, h*scale); }

        const float getCenterX() const { return this->x + this->w/2; }
        const float getCenterY() const { return this->y + this->h/2; }
        const xyfpair getCenter() const { return xyfpair(this->getCenterX(), this->getCenterY()); }

        const float getLeft() const { return this->x; }
        const float getRight() const { return this->x + this->w; }
        const float getTop() const { return this->y; }
        const float getBottom() const { return this->y + this->h; }

        const xyfpair getTopLeft() const { return xyfpair(this->getLeft(), this->getTop()); }
        const xyfpair getTopRight() const { return xyfpair(this->getRight(), this->getTop()); }
        const xyfpair getBottomLeft() const { return xyfpair(this->getLeft(), this->getBottom()); }
        const xyfpair getBottomRight() const { return xyfpair(this->getRight(), this->getBottom()); }
        

        const float getWidth() const { return this->w; }
        const float getHeight() const { return this->h; }

        const int getSide(const sides::Side side) const {
            return 
                side == sides::LEFT ? this->getLeft():
                side == sides::RIGHT ? this->getRight():
                side == sides::TOP ? this->getTop():
                side == sides::BOTTOM ? this->getBottom():
                sides::NONE;
        }

        const vector<xyfpair> getCorners() const
        {
            vector<xyfpair> corners;
            corners.push_back(this->getTopLeft());
            corners.push_back(this->getTopRight());
            corners.push_back(this->getBottomRight());
            corners.push_back(this->getBottomLeft());
            return corners;
        }

        void setCenterX(float x) { this->x = x - this->w/2; }
        void setCenterY(float y) { this->y = y - this->h/2; }
        void setCenter(float x, float y) { this->setCenterX(x); this->setCenterY(y); } 
        void setCenter(xyfpair xy) { this->setCenterX(xy.x); this->setCenterY(xy.y); } 
        
        void setLeft(float x) { this->x = x; }
        void setRight(float x) { this->x = x - this->w; }
        void setTop(float y) { this->y = y; }
        void setBottom(float y) { this->y = y - this->h; }

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

            if(!containedWithin(other)) SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Rectangle could not be contained within other");
        }

        /* checks is a Rectangle is valid */
        const bool isValidRect() const 
        {
            return this->x>=0 && this->y>=0 && this->w>=0 && this->h>=0;
        }

        float x, y, h, w;

};

#endif // !RECTANGLE_H