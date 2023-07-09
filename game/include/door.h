#ifndef DOOR_H
#define DOOR_H

#pragma once

#include "rectangle.h"
#include "globals.h"


class Door : public Rectangle
{
    public:
        Door(){}
        Door(Rectangle r, string destination, string spawn_side = ""):
            Rectangle(r.getLeft(), r.getTop(), r.getWidth(), r.getHeight()),
            _destination(destination),
            _spawn_side(spawn_side)
        {}

        const Rectangle getRectangle() { return this->getRectangle(); }
        const string getDestination() { return this->_destination; }
        const string getSpawnSide() { return this->_spawn_side; }

    private:
        string _destination;
        string _spawn_side;
};

#endif // !DOOR_H
