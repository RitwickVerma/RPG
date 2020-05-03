#include "player.h"
#include "graphics.h"

namespace o
{
    const float WALK_SPEED = 0.2;
    const string CHARACTER_SPRITE = "character.png";
    const int _h=96;
    const int _w=64;
}

Player::Player(){}

Player::Player(Graphics &graphics, int x, int y) :
    AnimatedSprite(graphics, o::CHARACTER_SPRITE, 0, 0, o::_w, o::_h, x, y, 100)
{

    this->setupAnimation();
    // this->playAnimation("idle_south");
    this->_facing=SOUTH;
}

void Player::setupAnimation()
{
    this->addAnimation(1, 0, o::_h*3, "idle_north", o::_w, o::_h, vector2(0,0));
    this->addAnimation(1, 0, o::_h*0, "idle_south", o::_w, o::_h, vector2(0,0));
    this->addAnimation(1, 0, o::_h*2, "idle_east", o::_w, o::_h, vector2(0,0));
    this->addAnimation(1, 0, o::_h*1, "idle_west", o::_w, o::_h, vector2(0,0));

    this->addAnimation(4, 0, o::_h*3, "walk_north", o::_w, o::_h, vector2(0,0));
    this->addAnimation(4, 0, o::_h*0, "walk_south", o::_w, o::_h, vector2(0,0));
    this->addAnimation(4, 0, o::_h*2, "walk_east", o::_w, o::_h, vector2(0,0));
    this->addAnimation(4, 0, o::_h*1, "walk_west", o::_w, o::_h, vector2(0,0));
}


void Player::moveNorth()
{
    this->_dx = 0;
    this->_dy = -o::WALK_SPEED;
    this->playAnimation("walk_north");
    this->_facing = NORTH;
}

void Player::moveSouth()
{
    this->_dx = 0;
    this->_dy = o::WALK_SPEED;
    this->playAnimation("walk_south");
    this->_facing = SOUTH;
}

void Player::moveEast()
{
    this->_dx = o::WALK_SPEED;
    this->_dy = 0;
    this->playAnimation("walk_east");
    this->_facing = EAST;
}

void Player::moveWest()
{
    this->_dx = -o::WALK_SPEED;
    this->_dy = 0;
    this->playAnimation("walk_west");
    this->_facing = WEST;
}

void Player::stopMoving()
{
    this->_dx = 0;
    this->_dy = 0;
    switch(this->_facing)
    {
        case NORTH:
            this->playAnimation("idle_north");
            break;
        case SOUTH:
            this->playAnimation("idle_south");
            break;
        case EAST:
            this->playAnimation("idle_east");
            break;
        case WEST:
            this->playAnimation("idle_west");
            break;
    }

}

void Player::animationDone(string animation)
{}

void Player::update(float timeElapsed)
{
    this->_x += this->_dx * timeElapsed;
    this->_y += this->_dy * timeElapsed;

    // cout<<this->_x<<" "<<this->_y<<endl;

    AnimatedSprite::update(timeElapsed);
}

void Player::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, this->_x, this->_y);
}