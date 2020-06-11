#include "thing.h"

Thing::Thing() {}

void Thing::addTile(Tile &tile)
{
    this->_thingTiles.push_back(tile);
}

void Thing::update(float elapsedTime){};

void Thing::draw(Graphics &graphics)
{
    for(Tile &tile : this->_thingTiles)
    {    // tile.setZ(tile.getZ() + this->z_comp);
        tile.draw(graphics);
    }
}

void Thing::setZ(float Z) { this->z_comp = Z; }

float Thing::getZ() { return this->z_comp; }

bool Thing::isEmpty() { return this->_thingTiles.empty(); }