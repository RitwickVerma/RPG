#ifndef XYPAIR_H
#define XYPAIR_H

#pragma once

using namespace std;

struct xyipair
{
    int x,y,w,h;
    xyipair() { x=y=w=h=0; }
    xyipair(int x_pos, int y_pos)
    {
        x=w=x_pos;
        y=h=y_pos;
    }

    xyipair zero() { return xyipair(0,0); }

    xyipair operator*(const float &scale) { return xyipair(x*scale, y*scale); }

    xyipair operator*(const xyipair &temp) { return xyipair(x*temp.x, y*temp.y); }

    xyipair operator+(const xyipair &temp) { return xyipair(x+temp.x, y+temp.y); }
   
    xyipair operator-(const xyipair &temp) { return xyipair(x-temp.x, y-temp.y); }

    long hash()
    {
        int a = x;
        int b = y;
        auto A = (long)(a >= 0 ? 2 * (long)a : -2 * (long)a - 1);
        auto B = (long)(b >= 0 ? 2 * (long)b : -2 * (long)b - 1);
        auto C = (long)((A >= B ? A * A + A + B : A + B * B) / 2);
        return a < 0 && b < 0 || a >= 0 && b >= 0 ? C : -C - 1;
    }

    void swapXY() { swap(x ,y); }
};

struct xyfpair
{
    float x,y;
    xyfpair() { x=y=0.0; }
    xyfpair(float x_pos, float y_pos)
    {
        x=x_pos;
        y=y_pos;
    }

    xyfpair zero() { return xyfpair(0,0); }

    xyfpair operator*(const float &scale) { return xyfpair(x*scale, y*scale); }

    xyfpair operator*(const xyfpair &temp) { return xyfpair(x*temp.x, y*temp.y); }

    xyfpair operator+(const xyfpair &temp) { return xyfpair(x+temp.x, y+temp.y); }
    
    xyfpair operator-(const xyfpair &temp) { return xyfpair(x-temp.x, y-temp.y); }

    bool operator==(const xyfpair &temp) { return x==temp.x && y==temp.y; }

    bool operator!=(const xyfpair &temp) { return x!=temp.x && y!=temp.y; }

    float dot(const xyfpair &temp) { return this->x*temp.x + this->y*temp.y; }
    
    void swapXY() { swap(x ,y); }

};

#endif // !XYPAIR_H