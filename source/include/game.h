#ifndef GAME_H
#define GAME_H

#pragma once

#include "player.h"
#include "level.h"
#include "globals.h"
#include "hud.h"
#include "textbox.h"
#include "graphics.h"
#include "ims.h"
#include "kbh.h"

class Game
{
public:
    Game();
    ~Game();

private:
    void gameLoop();
    void loadAllMaps(Graphics &graphics);
    void draw(Graphics &graphics);
    void update(float elapsedTime);
    Player _player;
    Level _level;
    IMS _inventory;
    Rectangle *_camera;
    HUD _hud;
    TextBox _textbox;
    Graphics _graphics;
    unordered_map<string, Level> _allMaps;

    friend class KeyboardHandler;
};

#endif