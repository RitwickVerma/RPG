#ifndef TILE_H
#define TILE_H

#pragma once

#include "globals.h"

struct Graphics;
struct SDL_Texture;

class Tile
{
    public:
        Tile();
        Tile(SDL_Texture *tileset, int ID, xyipair size, xyipair tilesetPosition, xyfpair position);   
        void update(float elapsedTime);
        void draw(Graphics &graphics);
        void addOffset(xyfpair offset);
        const xyfpair getXY() const { return this->_position; }

    private:
        int _ID;
        SDL_Texture *_tileset;
        xyipair _size;
        xyipair _tilesetPosition;
        xyfpair _position;
};

#endif // !TILE_H