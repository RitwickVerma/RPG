#ifndef SIGNPOST_H
#define SIGNPOST_H

#pragma once

#include "rectangle.h"
#include "globals.h"

class SignPost : public Rectangle
{
public:
    SignPost() {}
    SignPost(Rectangle r, string message) : Rectangle(r.getLeft(), r.getTop(), r.getWidth(), r.getHeight()),
                                            _message(message)
    {
    }

    const Rectangle getRectangle() { return this->getRectangle(); }
    const string getMessage() { return this->_message; }

private:
    string _message;
};

#endif // !DOOR_H
