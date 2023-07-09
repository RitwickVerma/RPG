#include "kbh.h"
#include "game.h"

void keyboard_handler::poll()
{
    begin_new_frame();

    if (SDL_PollEvent(&m_event) == 1)
    {
        if (m_event.type == SDL_KEYDOWN)
        {
            if (m_event.key.repeat == 0)
                key_down_event(m_event);
        }
        else if (m_event.type == SDL_KEYUP)
            key_up_event(m_event);
        else if (m_event.type == SDL_QUIT)
            exit(EXIT_SUCCESS);
    }
}

void keyboard_handler::handle(Game &game)
{
    poll();

    if (was_key_pressed(SDL_SCANCODE_ESCAPE))
        exit(EXIT_SUCCESS);

    if (was_key_pressed(SDL_SCANCODE_SPACE))
        game.m_player.attack();

    if (is_key_held(SDL_SCANCODE_A))
        game.m_player.moveWest();
    else if (is_key_held(SDL_SCANCODE_D))
        game.m_player.moveEast();
    // else if(!isKeyHeld(SDL_SCANCODE_A) and !isKeyHeld(SDL_SCANCODE_D))
    //     game._player.stopMoving();

    if (is_key_held(SDL_SCANCODE_W))
        game.m_player.moveNorth();
    else if (is_key_held(SDL_SCANCODE_S))
        game.m_player.moveSouth();
    // else if(!isKeyHeld(SDL_SCANCODE_W) and !isKeyHeld(SDL_SCANCODE_S))
    //     game._player.stopMoving();

    if (!is_key_held(SDL_SCANCODE_W) and !is_key_held(SDL_SCANCODE_S) and
        !is_key_held(SDL_SCANCODE_A) and !is_key_held(SDL_SCANCODE_D) and
        !was_key_pressed(SDL_SCANCODE_SPACE))
        game.m_player.stopMoving();

    if (is_key_held(SDL_SCANCODE_E))
        game.m_player.interact(true);
    else if (!isKeyHeld(SDL_SCANCODE_E))
        game.m_player.interact(false);

    if (was_key_pressed(SDL_SCANCODE_1))
        game.m_inventory.setEquippedWeapon(inv::weapons::Weapon::BASIC_BOW);
    else if (was_key_pressed(SDL_SCANCODE_2))
        game.m_inventory.setEquippedWeapon(inv::weapons::Weapon::BASIC_AXE);
    else if (was_key_pressed(SDL_SCANCODE_3))
        game.m_inventory.setEquippedWeapon(inv::weapons::Weapon::BASIC_SPEAR);
    else if (was_key_pressed(SDL_SCANCODE_G))
        game.m_inventory.setEquippedWeapon(inv::weapons::Weapon::NONE);

    if (is_key_held(SDL_SCANCODE_GRAVE))
        global::DEV_MODE = true;
    else if (!is_key_held(SDL_SCANCODE_GRAVE))
        global::DEV_MODE = false;

    /* Dev mode*/
    if (global::DEV_MODE)
    {
        if (is_key_held(SDL_SCANCODE_M))
        {
            string mapname = game.m_level.getMapName();
            game.m_allMaps[mapname] = Level(game.m_graphics, mapname, &game.m_player);
            game.m_level = game.m_allMaps[mapname];
        }
    }
}