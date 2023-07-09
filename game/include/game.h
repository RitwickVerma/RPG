#ifndef GAME_H
#define GAME_H

#include "uncopyable.h"
#pragma once

#include "globals.h"
#include "graphics.h"
#include "hud.h"
#include "ims.h"
#include "kbh.h"
#include "level.h"
#include "player.h"
#include "textbox.h"

class Game
{
public:
    Game();
    ~Game();

    // Non-copyable class
    Game(const Game&) = delete;
    Game& operator=(Game&) = delete;

private:
    void game_loop();
    void load_all_maps(Graphics& graphics);
    void draw(Graphics& graphics);
    void update(float elapsed_time);

    Graphics m_graphics;
    Player m_player;
    Level m_level;
    IMS m_inventory;
    Rectangle* m_camera;
    HUD m_hud;
    TextBox m_textbox;

    unordered_map<string, Level> m_all_maps;

    friend class KeyboardHandler;
};

#endif
