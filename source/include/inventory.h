#ifndef INVENTORY_H
#define INVENTORY_H

#pragma once

#include "graphics.h"
#include "weapon.h"
#include "globals.h"
// #include "player.h"
struct Player;

class Inventory
{
    public:
        Inventory(){};
        Inventory(Graphics &graphics, Player *player);

        void update(float elapsedTime);
        void draw(Graphics &graphics);
        void drawEquipped(Graphics &graphics);

        void equipWeapon(inv::weapon::Weapons weapon_type);
        void showInventory(bool show);
        void populateInventory();

    private:
        bool _showInventory;
        Weapon *_currentWeapon;
        Player *_player;
        Graphics *_graphics;
        unordered_map<inv::weapon::Weapons, Weapon*> _allWeapons;
};

#endif // !INVENTORY_H