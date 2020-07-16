#ifndef IMS_H
#define IMS_H

#pragma once

#include "graphics.h"
#include "weapon.h"
#include "globals.h"
// #include "player.h"
struct Player;

struct weapon_info
{
    inv::weapons::Weapon type;
    inv::weapons::Class weaponClass;
    weapon_info()
    {
        this->type = inv::weapons::Weapon::NONE;
        this->weaponClass = inv::weapons::Class::NONE;
    }

    weapon_info(inv::weapons::Weapon type, inv::weapons::Class weaponClass)
    {
        this->type = type;
        this->weaponClass = weaponClass;
    }
};

class IMS
{
public:
    IMS(){};
    IMS(Graphics &graphics, Player *player);

    void update(float elapsedTime);
    void draw(Graphics &graphics);
    void drawEquipped(Graphics &graphics);

    void setEquippedWeapon(inv::weapons::Weapon weapon_type);
    weapon_info getEquippedWeaponInfo();

    void showInventory(bool show);
    void populateInventory();

private:
    bool _showInventory;
    Player *_player;
    Graphics *_graphics;
    Weapon *_currentEquippedWeapon;
    unordered_map<inv::weapons::Weapon, Weapon *> _allWeapons;
};

#endif