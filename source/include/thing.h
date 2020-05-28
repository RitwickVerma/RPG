#ifndef THING_H
#define THING_H

#pragma once

#include "globals.h"
#include "tile.h"

class Thing
{
    public:
        Thing();
       void addTile(Tile &tile);
       void draw(Graphics &graphics);
       void setZ(float Z);
       float getZ();
       bool isEmpty();

    private:
        float z_comp;
        vector<Tile> _thingTiles;
};

#endif // !THING_H