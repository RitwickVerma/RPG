#include "player.h"
#include "graphics.h"

namespace o
{
    const float WALK_SPEED = 0.2f;
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    const string CHARACTER_SPRITE = "character48.png";
    int _w=48;
    int _h=72;
}

Player::Player(){}

Player::Player(Graphics &graphics, xyipair spawnPoint, Rectangle *camera) :
    AnimatedSprite(graphics, o::CHARACTER_SPRITE, 0, 0, o::_w, o::_h, spawnPoint.x, spawnPoint.y, 100)
{
    this->_dx=0;
    this->_dy=0;
    this->_camera=camera;
    this->_grounded=false;
    this->setupAnimation();
    this->_facing=SOUTH;
    
    this->_camera->setCenter(Rectangle(this->_x, this->_y, this->_destRect.w, this->_destRect.h).getCenter());
}

void Player::setupAnimation()
{
    this->addAnimation(1, 0, o::_h*3, "idle_north", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*0, "idle_south", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*2, "idle_east", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*1, "idle_west", o::_w, o::_h, xyipair(0,0));

    this->addAnimation(4, 0, o::_h*3, "walk_north", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(4, 0, o::_h*0, "walk_south", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(4, 0, o::_h*2, "walk_east", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(4, 0, o::_h*1, "walk_west", o::_w, o::_h, xyipair(0,0));
}

void Player::setCurrentLevel(Level *level)
{
    this->_currentLevel = level;
}

Level * Player::getCurrentLevel()
{
    return this->_currentLevel;
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

void Player::handleTileCollision(vector<Rectangle> colliding)
{
   for( Rectangle r : colliding)
   {
       sides::Side collisionSide = Sprite::getCollisionSide(r);
       if(collisionSide != sides::NONE)
       {
           switch(collisionSide)
           {
               case sides::LEFT:
                    this->_x=r.getRight() + 1 - abs(Rectangle(this->_destRect).getLeft() - this->_boundingBox.getLeft());
                    this->_dx=0;
                    break;
               case sides::RIGHT:
                    this->_x=r.getLeft() - 1 - abs(Rectangle(this->_destRect).getLeft() - this->_boundingBox.getRight());
                    this->_dx=0;
                    break;
               case sides::TOP:
                    this->_y=r.getBottom() + 1 - abs(Rectangle(this->_destRect).getTop() - this->_boundingBox.getTop());
                    this->_dy=0;
                    break;
               case sides::BOTTOM:
                    this->_y=r.getTop() - 1 - abs(Rectangle(this->_destRect).getTop() - this->_boundingBox.getBottom());
                    this->_dy=0;
                    this->_grounded = (this->_currentLevel->hasGravity()) ? true : false;
                    break;
            
           }
       }
   } 
}

void Player::update(float timeElapsed)
{
    AnimatedSprite::update(timeElapsed);

    // Apply Gravity
    if(this->_dy <= o::GRAVITY_CAP && this->_currentLevel->hasGravity())
        this->_dy += o::GRAVITY * timeElapsed; 

    this->_x += this->_dx * timeElapsed;
    this->_y += this->_dy * timeElapsed;
    
    if(!Rectangle(this->_x, this->_y, this->_destRect.w, this->_destRect.h).containedWithin(*this->_camera))
    {
        this->_x -= this->_dx * timeElapsed;
        this->_y -= this->_dy * timeElapsed;
    }

    this->_camera->setCenter(Rectangle(this->_x, this->_y, this->_destRect.w, this->_destRect.h).getCenter());
    
    this->_camera->containWithin(Rectangle(0, 0, this->_currentLevel->getMapSize().x, this->_currentLevel->getMapSize().y));

    this->_boundingBox = Rectangle(this->_x+4, this->_y+46, o::_w-8, 16);
}

void Player::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, this->_x-this->_camera->getLeft(), this->_y-this->_camera->getTop());
}