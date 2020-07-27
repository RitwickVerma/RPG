#ifndef WEAPON_H
#define WEAPON_H

#pragma once

#include "globals.h"
#include "animatedsprite.h"
#include "graphics.h"

struct Player;

struct weapon_info
{
    inv::weapons::Weapon type;
    inv::weapons::Class weaponClass;
    string filename;
    weapon_info()
    {
        this->type = inv::weapons::Weapon::NONE;
        this->weaponClass = inv::weapons::Class::NONE;
        this->filename = "";
    }

    weapon_info(string filename, inv::weapons::Weapon type)
    {
        this->type = type;
        this->filename = filename;

        switch (type)
        {
        case inv::weapons::Weapon::NONE:
        case inv::weapons::Weapon::EXTRA:
            this->weaponClass = inv::weapons::Class::NONE;
            break;

        case inv::weapons::Weapon::BASIC_BOW:
            this->weaponClass = inv::weapons::Class::SHOOT;
            break;

        case inv::weapons::Weapon::BASIC_AXE:
            this->weaponClass = inv::weapons::Class::SLASH;
            break;

        case inv::weapons::Weapon::BASIC_SPEAR:
            this->weaponClass = inv::weapons::Class::THRUST;
            break;
        }
    }
};

class Weapon : public AnimatedSprite
{
public:
    Weapon(Graphics &graphics, weapon_info, Player *);
    void update(float elapsedTime);
    void draw(Graphics &graphics);
    void animationDone(string currentAnimation);

    weapon_info getWeaponInfo();

    inv::weapons::Weapon getType();
    inv::weapons::Class getClass();

    void setupAnimation();

private:
    int _damage;
    int _range;
    Player *_player;
    inv::weapons::Weapon _type;
    inv::weapons::Class _class;
    weapon_info _info;
    Weapon *_extraWeapon;
};

#endif // !WEAPON_H
