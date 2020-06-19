#ifndef DOOR_H
#define DOOR_H

#pragma once

#include "rectangle.h"
#include "globals.h"


class Door : public Rectangle
{
    public:
        Door();
        Door(Rectangle r, string destination):
            Rectangle(r.getLeft(), r.getTop(), r.getWidth(), r.getHeight()),
            _destination(destination)
        {}

        const Rectangle getRectangle() { return this->getRectangle(); }
        const string getDestination() { return this->_destination; }

    private:
        string _destination;
};

#endif // !DOOR_H
