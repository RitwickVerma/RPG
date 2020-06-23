#ifndef GAME_H
#define GAME_H

#pragma once

#include "player.h"
#include "level.h"
#include "globals.h"
#include "hud.h"
#include "graphics.h"

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
        Rectangle *_camera;
        HUD _hud;
        Graphics _graphics;
        unordered_map<string, Level> _allMaps;

};

#endif