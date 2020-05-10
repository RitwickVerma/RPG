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
        Player(Graphics &graphics, xyipair spawnPoint, Rectangle *camera = NULL);
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
        void setCamera(Rectangle *camera) { this->_camera = camera; }

        Rectangle getSpriteBox() { return Rectangle(this->_destRect); }

        void handleTileCollision(vector<Rectangle> colliding);
        const float getX() const { return this->_x; }
        const float getY() const { return this->_y; }

    private:
        float _dx, _dy;
        Direction _facing;
        Level *_currentLevel;
        Rectangle *_camera;
        bool _grounded;
};

#endif // !1P PLAYER_H