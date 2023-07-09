#ifndef THING_H
#define THING_H

#pragma once

#include "globals.h"
#include "tile.h"
#include "animatedtile.h"
#include "renderable.h"

class Thing : public Renderable
{
    public:
       Thing();
       void addTile(Tile &tile);
       void addTile(AnimatedTile &tile);
       void update(float elapsedTime);
       void draw(Graphics &graphics);
       void setZ(float Z);
       float getZ();
       bool isEmpty();

    private:
        float z_comp;
        vector<variant<Tile, AnimatedTile>> _thingTiles;
};

#endif // !THING_H