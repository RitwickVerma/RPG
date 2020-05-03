#ifndef PLAYER_H
#define PLAYER_H

#include "animatedsprite.h"

struct Graphics;

class Player : public AnimatedSprite
{
    public:
        Player();
        Player(Graphics &graphics, int x, int y);
        void draw(Graphics &graphics);
        void update(float elapsedTime);

        void moveNorth();
        void moveSouth();
        void moveEast();
        void moveWest();
        void stopMoving();

        virtual void animationDone(string currentAnimation);
        virtual void setupAnimation();

    private:
        float _dx, _dy;
        Direction _facing;
};

#endif // !1P PLAYER_H