#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "sprite.h"

struct Player;

class TextBox
{
public:
    TextBox();
    TextBox(Graphics &graphics);
    void update(float elapsedTime);
    void draw(Graphics &graphics);

private:
    Sprite _textFrame;
    Sprite _portrait;
    Sprite _portraitFrame;
    Sprite _connector;
};

#endif // !HUD_H
