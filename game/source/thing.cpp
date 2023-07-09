#include "thing.h"

Thing::Thing() {}

void Thing::addTile(Tile &tile)
{
    this->_thingTiles.push_back(tile);
}

void Thing::addTile(AnimatedTile &tile)
{
    this->_thingTiles.push_back(tile);
}

void Thing::update(float elapsedTime){};

void Thing::draw(Graphics &graphics)
{
    for(auto &tile : this->_thingTiles)
    {    // tile.setZ(tile.getZ() + this->z_comp);
        // tile.draw(graphics);
        visit([&graphics](auto &&arg) { arg.draw(graphics); }, tile);
    }
}

void Thing::setZ(float Z) { this->z_comp = Z; }

float Thing::getZ() { return this->z_comp; }

bool Thing::isEmpty() { return this->_thingTiles.empty(); }