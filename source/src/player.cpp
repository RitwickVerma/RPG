#include "player.h"
#include "graphics.h"

namespace o
{
    const float WALK_SPEED = 0.2f;
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    const string CHARACTER_SPRITE = "player.png";
    int _w=64;
    int _h=64;
}

Player::Player(){}

Player::Player(Graphics &graphics, xyipair spawnPoint, Rectangle *camera) :
    AnimatedSprite(graphics, o::CHARACTER_SPRITE, 0, 0, o::_w, o::_h, spawnPoint.x, spawnPoint.y, 75)
{
    this->_dx=0;
    this->_dy=0;
    this->_camera=camera;
    this->_grounded=false;
    this->setupAnimation();
    this->_facing=SOUTH;
    
    this->_camera->setCenter(this->_sprite.getCenter());
}

void Player::setupAnimation()
{    
    this->addAnimation(1, 0, o::_h*8, "idle_north", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*10, "idle_south", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*11, "idle_east", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(1, 0, o::_h*9, "idle_west", o::_w, o::_h, xyipair(0,0));

    this->addAnimation(9, 0, o::_h*8, "walk_north", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(9, 0, o::_h*10, "walk_south", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(9, 0, o::_h*11, "walk_east", o::_w, o::_h, xyipair(0,0));
    this->addAnimation(9, 0, o::_h*9, "walk_west", o::_w, o::_h, xyipair(0,0));
}

void Player::animationDone(string animation)
{}

void Player::updateBoundingBox()
{
    this->_boundingBox = Rectangle(this->_sprite.x+14, this->_sprite.y+52, o::_w-32, 12);
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


void Player::undoMove(float timeElapsed)
{
    this->_sprite.x -= this->_dx * timeElapsed;
    this->_sprite.y -= this->_dy * timeElapsed;
    this->updateBoundingBox();
}

void Player::makeMove(float timeElapsed)
{
    this->_sprite.x += this->_dx * timeElapsed;
    this->_sprite.y += this->_dy * timeElapsed;
    this->updateBoundingBox();
}

void Player::handleTileCollision(vector<Rectangle> &colliding)
{
    for( Rectangle &r : colliding)
    {
        sides::Side collisionSide = Sprite::getCollisionSide(r);
        if(collisionSide != sides::NONE)
        {
            switch(collisionSide)
            {
                case sides::LEFT:
                    this->_sprite.x=r.getRight() + 1 - abs(this->_sprite.getLeft() - this->_boundingBox.getLeft());
                    this->_dx=0;
                    break;
                case sides::RIGHT:
                    this->_sprite.x=r.getLeft() - 1 - abs(this->_sprite.getLeft() - this->_boundingBox.getRight());
                    this->_dx=0;
                    break;
                case sides::TOP:
                    this->_sprite.y=r.getBottom() + 1 - abs(this->_sprite.getTop() - this->_boundingBox.getTop());
                    this->_dy=0;
                    break;
                case sides::BOTTOM:
                    this->_sprite.y=r.getTop() - 1 - abs(this->_sprite.getTop() - this->_boundingBox.getBottom());
                    this->_dy=0;
                    this->_grounded = (this->_currentLevel->hasGravity()) ? true : false;
                    break;
            }
        }
    } 
}

void Player::handleSlopeCollision(vector<Slope> &colliding)
{
    for( Slope &slope : colliding)
    {
        continue;
    }
}

void Player::update(float timeElapsed)
{
    AnimatedSprite::update(timeElapsed);

    // Apply Gravity
    if(this->_dy <= o::GRAVITY_CAP && this->_currentLevel->hasGravity())
        this->_dy += o::GRAVITY * timeElapsed; 

    // Move player by changing x, y by velocity dx, dy
    // this->_sprite.x += this->_dx * timeElapsed;
    // this->_sprite.y += this->_dy * timeElapsed;
    // this->updateBoundingBox();
    this->makeMove(timeElapsed);

    // Check if the player is within camera after change. If not, move player back.
    if(!this->_sprite.containedWithin(*this->_camera))
    {
        this->undoMove(timeElapsed);
        this->stopMoving();
    }


}

void Player::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics, this->_sprite.x-this->_camera->getLeft(), this->_sprite.y-this->_camera->getTop());
}