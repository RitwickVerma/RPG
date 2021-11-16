#ifndef TEXTBOX_H
#define TEXTBOX_H

#include "sprite.h"
#include "globals.h"

struct Player;

class TextBox
{
public:
    TextBox();
    TextBox(Graphics &graphics);
    void show(bool show = true);
    TextBox &showForTime(float time);
    TextBox &setText(string message);
    void update(float elapsedTime);
    void draw(Graphics &graphics);

private:
    Graphics *_graphics;
    Sprite _textFrame;
    Sprite _portrait;
    Sprite _portraitFrame;
    Sprite _connector;
    string _text;
    SDL_Texture *_textTexture;
    bool _showTextBox;
    float _showTillTime;
};

#endif // !HUD_H
