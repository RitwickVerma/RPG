#include "player.h"
#include "graphics.h"

namespace o
{
    const float WALK_SPEED = 0.25f;
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
    this->stopMoving();
    this->_interact = false;
    this->_lockMovement = false;
    
    this->_maxHealth = 100;
    this->_currentHealth = 100;
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

    this->addAnimation(8, o::_w*3, o::_h*16, "shoot_north", o::_w, o::_h, xyipair(0,0), 50);
    this->addAnimation(8, o::_w*3, o::_h*18, "shoot_south", o::_w, o::_h, xyipair(0,0), 50);
    this->addAnimation(8, o::_w*3, o::_h*19, "shoot_east", o::_w, o::_h, xyipair(0,0), 50);
    this->addAnimation(8, o::_w*3, o::_h*17, "shoot_west", o::_w, o::_h, xyipair(0,0), 50);
}

void Player::animationDone(string animation)
{
    if(animation.find("shoot") != string::npos)
    {
        this->_lockAnimation = false;
        this->_lockMovement = false;
    }
}

void Player::updateBoundingBox()
{
    this->_boundingBox = Rectangle(this->_sprite.x+16, this->_sprite.y+52, o::_w-32, 12);
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

void Player::interact(bool interact)
{
    this->_interact = interact;
}

void Player::shoot()
{
    this->_lockAnimation = false;
    this->_dx = this->_dy = 0;
    switch(this->_facing)
    {
        case NORTH:
            this->playAnimation("shoot_north", true, false);
            break;
        case SOUTH:
            this->playAnimation("shoot_south", true, false);
            break;
        case EAST:
            this->playAnimation("shoot_east", true, false);
            break;
        case WEST:
            this->playAnimation("shoot_west", true, false);
            break;
    }
    this->_lockAnimation = true;
    // this->_lockMovement = true;
}

void Player::undoMove(float elapsedTime)
{
    this->_sprite.x -= this->_dx * elapsedTime;
    this->_sprite.y -= this->_dy * elapsedTime;
    this->updateBoundingBox();
}

void Player::makeMove(float elapsedTime)
{
    // if(this->_lockMovement) return;

    this->_sprite.x += this->_dx * elapsedTime;
    this->_sprite.y += this->_dy * elapsedTime;
    this->updateBoundingBox();
}


void Player::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);

    // Apply Gravity
    if(this->_dy <= o::GRAVITY_CAP && this->_currentLevel->getGravity())
        this->_dy += o::GRAVITY * elapsedTime; 

    // Move player by changing x, y by velocity dx, dy
    // if(!this->_lockAnimation and this->_currentAnimation.find("shoot") == string::npos)
        this->makeMove(elapsedTime);

    // Contain Player within Camera.
    this->_sprite.containWithin(*this->_camera);
}

void Player::draw(Graphics &graphics)
{
    // AnimatedSprite::draw(graphics, this->_sprite.x-this->_camera->getLeft(), this->_sprite.y-this->_camera->getTop());
    if(this->_visible)
    {
        SDL_Rect destRect = {
                                this->_sprite.x+this->_offsets[this->_currentAnimation].x,
                                this->_sprite.y+this->_offsets[this->_currentAnimation].y,
                                (int)this->_sprite.w , (int)this->_sprite.h  
                            };

        SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];

        this->makeRenderable(this->_boundingBox.getBottom(), this->_spriteSheet, sourceRect, destRect, "player");
        graphics.addToRenderQueue(*this);
    }
}