#ifndef GAME_H
#define GAME_H

#pragma once

#include "player.h"
#include "level.h"
#include "globals.h"

struct Graphics;

class Game
{
    public:
        Game();
        ~Game();
    private:
        void gameLoop();
        void draw(Graphics &graphics);
        void update(float elapsedTime);
        Player _player;
        Level _level;
        Rectangle *_camera;
};

#endif