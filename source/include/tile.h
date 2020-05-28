#ifndef TILE_H
#define TILE_H

#pragma once

#include "globals.h"

struct Graphics;
struct SDL_Texture;
struct Rectangle;
class Tile
{
    public:
        Tile();
        Tile(SDL_Texture *tileset, int ID, xyipair size, xyipair tilesetPosition, xyfpair position, float Z=-100);   
        void update(float elapsedTime);
        void draw(Graphics &graphics);
        const xyfpair getPosition() const { return this->_position; }

        Rectangle getRectangle();
        const float getZ() const { return this->z_comp; }
        void setZ(float Z) { this->z_comp = Z; }

    private:
        int _ID;
        float z_comp;
        SDL_Texture *_tileset;
        xyipair _size;
        xyipair _tilesetPosition;
        xyfpair _position;
        xyfpair _offset;
};

#endif // !TILE_H