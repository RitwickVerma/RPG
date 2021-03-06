#ifndef TILE_H
#define TILE_H

#pragma once

#include "globals.h"
#include "renderable.h"

struct Graphics;
struct SDL_Texture;
struct Rectangle;
struct animated_tile_frame
{
    animated_tile_frame(SDL_Texture *texture, int duration, xyipair position = xyipair(0,0))
    {
        frameTexture = texture;
        tilesetPosition = position;
        frameDuration = duration;
    }

    SDL_Texture *frameTexture;
    int frameDuration;
    xyipair tilesetPosition;
};

class Tile : public Renderable
{
    public:
        Tile();
        Tile(SDL_Texture *tileset, int ID, xyipair size, xyipair tilesetPosition, xyfpair position, float Z=-100);   
        virtual void update(float elapsedTime);
        virtual void draw(Graphics &graphics);
        virtual void addTileFrame(animated_tile_frame tileFrame);
        const xyfpair getPosition() const { return this->_position; }

        Rectangle getRectangle();
        const float getZ() const { return this->z_comp; }
        void setZ(float Z) { this->z_comp = Z; }

    protected:
        int _ID;
        float z_comp;
        SDL_Texture *_tileset;
        xyipair _size;
        xyipair _tilesetPosition;
        xyfpair _position;
        xyfpair _offset;
};

#endif // !TILE_H