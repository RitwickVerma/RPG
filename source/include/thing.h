#ifndef THING_H
#define THING_H

#pragma once

#include "globals.h"
#include "renderable.h"
#include "tile.h"

class Thing : protected Renderable
{
    protected:
       

    private:
    vector<Tile> _thingTiles;
};

#endif // !THING_H