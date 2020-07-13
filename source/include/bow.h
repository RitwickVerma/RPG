#ifndef BOW_H
#define BOW_H

#pragma once

#include "weapon.h"

struct Player;

class Bow : public Weapon
{
    public:
        Bow(Graphics &graphics, Player*);
        void update(float elapsedTime);
        void animationDone(string currentAnimation);
        // void setupAnimation();
    private:
        Player *_player;
};

#endif