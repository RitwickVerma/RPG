#include "kbh.h"
#include "game.h"

KeyboardHandler::KeyboardHandler() : Input()
{
}

void KeyboardHandler::poll()
{
    this->beginNewFrame();
    if (SDL_PollEvent(&this->event))
    {
        if (this->event.type == SDL_KEYDOWN)
        {
            if (this->event.key.repeat == 0)
                this->keyDownEvent(this->event);
        }
        else if (this->event.type == SDL_KEYUP)
            this->keyUpEvent(this->event);
        else if (this->event.type == SDL_QUIT)
            exit(EXIT_SUCCESS);
    }
}

void KeyboardHandler::handle(Game &game)
{
    this->poll();

    if (this->wasKeyPressed(SDL_SCANCODE_ESCAPE))
        exit(EXIT_SUCCESS);

    if (this->wasKeyPressed(SDL_SCANCODE_SPACE))
        game._player.attack();

    if (this->isKeyHeld(SDL_SCANCODE_A))
        game._player.moveWest();
    else if (this->isKeyHeld(SDL_SCANCODE_D))
        game._player.moveEast();
    // else if(!this->isKeyHeld(SDL_SCANCODE_A) and !this->isKeyHeld(SDL_SCANCODE_D))
    //     game._player.stopMoving();

    if (this->isKeyHeld(SDL_SCANCODE_W))
        game._player.moveNorth();
    else if (this->isKeyHeld(SDL_SCANCODE_S))
        game._player.moveSouth();
    // else if(!this->isKeyHeld(SDL_SCANCODE_W) and !this->isKeyHeld(SDL_SCANCODE_S))
    //     game._player.stopMoving();

    if (!this->isKeyHeld(SDL_SCANCODE_W) and !this->isKeyHeld(SDL_SCANCODE_S) and
        !this->isKeyHeld(SDL_SCANCODE_A) and !this->isKeyHeld(SDL_SCANCODE_D) and
        !this->wasKeyPressed(SDL_SCANCODE_SPACE))
        game._player.stopMoving();

    if (this->isKeyHeld(SDL_SCANCODE_E))
        game._player.interact(true);
    else if (!this->isKeyHeld(SDL_SCANCODE_E))
        game._player.interact(false);

    if (this->wasKeyPressed(SDL_SCANCODE_1))
        game._inventory.setEquippedWeapon(inv::weapons::Weapon::BASIC_BOW);
    else if (this->wasKeyPressed(SDL_SCANCODE_2))
        game._inventory.setEquippedWeapon(inv::weapons::Weapon::BASIC_AXE);
    else if (this->wasKeyPressed(SDL_SCANCODE_3))
        game._inventory.setEquippedWeapon(inv::weapons::Weapon::BASIC_SPEAR);
    else if (this->wasKeyPressed(SDL_SCANCODE_G))
        game._inventory.setEquippedWeapon(inv::weapons::Weapon::NONE);

    if (this->isKeyHeld(SDL_SCANCODE_GRAVE))
        global::DEV_MODE = true;
    else if (!this->isKeyHeld(SDL_SCANCODE_GRAVE))
        global::DEV_MODE = false;

    ////////////
    //Dev Mode//
    if (global::DEV_MODE)
    {
        if (this->isKeyHeld(SDL_SCANCODE_M))
        {
            string mapname = game._level.getMapName();
            game._allMaps[mapname] = Level(game._graphics, mapname, &game._player);
            game._level = game._allMaps[mapname];
        }
    }
    ////////////
}