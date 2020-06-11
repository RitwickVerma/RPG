#ifndef ANIMATEDTILE_H
#define ANIMATEDTILE_H  

#pragma once

#include "tile.h"

struct animated_tile_frame;
class AnimatedTile : public Tile
{
    public:
        AnimatedTile();
        AnimatedTile(int ID, xyipair size, xyipair tilesetPosition, xyfpair position, float Z = -100);

        void update(float elapsedTime);

        void draw(Graphics &graphics);

        void addTileFrame(animated_tile_frame tileFrame);

    
    private:
        vector<animated_tile_frame> _frameTiles;
        int _frameIndex;
        float _timeForUpdate;
    
};

struct animated_tile_frame
{
    animated_tile_frame(SDL_Texture *texture, SDL_Rect rect, int duration)
    {
        frameTexture = texture;
        sourceRect = rect;
        frameDuration = duration;
    }

    SDL_Texture *frameTexture;
    int frameDuration;
    SDL_Rect sourceRect;
};

#endif