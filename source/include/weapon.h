#ifndef WEAPON_H
#define WEAPON_H

#pragma once

#include "globals.h"
#include "animatedsprite.h"
#include "graphics.h"

struct Player;

class Weapon : public AnimatedSprite
{
public:
    Weapon(Graphics &graphics, Player *, string filename, int damage);
    virtual void update(float elapsedTime);
    virtual void draw(Graphics &graphics);

    virtual inv::weapons::Weapon getType() = 0;
    virtual inv::weapons::Class getClass() = 0;
    // virtual void animationDone(string currentAnimation);
    void setupAnimation();

protected:
    int _damage;
    int _range;
    Player *_player;
    // inv::weapons::Weapon _weaponType;
};

#endif // !WEAPON_H
