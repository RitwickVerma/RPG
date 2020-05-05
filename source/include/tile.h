#ifndef TILE_H
#define TILE_H

#include "globals.h"

struct Graphics;
struct SDL_Texture;

class Tile
{
    public:
        Tile();
        Tile(SDL_Texture *tileset, xypair size, xypair tilesetPosition, xypair position);   
        void update(float elapsedTime);
        void draw(Graphics &graphics);

    private:
        SDL_Texture *_tileset;
        xypair _size;
        xypair _tilesetPosition;
        xypair _position;
};

#endif // !TILE_H