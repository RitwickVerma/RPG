#ifndef PLAYER_H
#define PLAYER_H
  
#pragma once

#include "animatedsprite.h"
#include "level.h"
#include "rectangle.h"

struct Graphics;

class Player : public AnimatedSprite
{
    public:
        Player();
        Player(Graphics &graphics, xypair spawnPoint);
        void draw(Graphics &graphics);
        void update(float elapsedTime);

        void moveNorth();
        void moveSouth();
        void moveEast();
        void moveWest();
        void stopMoving();

        virtual void animationDone(string currentAnimation);
        virtual void setupAnimation();

        void setCurrentLevel(Level *level);
        Level * getCurrentLevel();

        void handleTileCollision(vector<Rectangle> colliding);
        const float getX() const;
        const float getY() const;

    private:
        float _dx, _dy;
        Direction _facing;
        Level *_currentLevel;
        bool _grounded;
};

#endif // !1P PLAYER_H