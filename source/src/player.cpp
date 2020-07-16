#include "player.h"
#include "graphics.h"
#include "ims.h"

namespace o
{
    const float WALK_SPEED = 0.25f;
    const float GRAVITY = 0.002f;
    const float GRAVITY_CAP = 0.8f;
    const string CHARACTER_SPRITE = "player.png";
    const int _w = 64;
    const int _h = 64;
} // namespace o

Player::Player() {}

Player::Player(Graphics &graphics, xyipair spawnPoint, Rectangle *camera) : // _inventory(inventory),
                                                                            AnimatedSprite(graphics, o::CHARACTER_SPRITE, 0, 0, o::_w, o::_h, spawnPoint.x, spawnPoint.y, 75)
{
    this->_dx = 0;
    this->_dy = 0;
    this->_camera = camera;
    this->_grounded = false;
    this->setupAnimation();
    this->_facing = direction::SOUTH;
    this->stopMoving();
    this->_interact = false;
    this->_lockMovement = false;

    this->_maxHealth = 100;
    this->_currentHealth = 100;
}

void Player::setupAnimation()
{
    this->addAnimation(1, o::_w * 0, o::_h * 8, "idle_north", o::_w, o::_h, xyipair(0, 0));
    this->addAnimation(1, o::_w * 0, o::_h * 10, "idle_south", o::_w, o::_h, xyipair(0, 0));
    this->addAnimation(1, o::_w * 0, o::_h * 11, "idle_east", o::_w, o::_h, xyipair(0, 0));
    this->addAnimation(1, o::_w * 0, o::_h * 9, "idle_west", o::_w, o::_h, xyipair(0, 0));

    this->addAnimation(9, o::_w * 0, o::_h * 8, "walk_north", o::_w, o::_h, xyipair(0, 0));
    this->addAnimation(9, o::_w * 0, o::_h * 10, "walk_south", o::_w, o::_h, xyipair(0, 0));
    this->addAnimation(9, o::_w * 0, o::_h * 11, "walk_east", o::_w, o::_h, xyipair(0, 0));
    this->addAnimation(9, o::_w * 0, o::_h * 9, "walk_west", o::_w, o::_h, xyipair(0, 0));

    this->addAnimation(7, o::_w * 0, o::_h * 0, "spellcast_north", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(7, o::_w * 0, o::_h * 2, "spellcast_south", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(7, o::_w * 0, o::_h * 3, "spellcast_east", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(7, o::_w * 0, o::_h * 1, "spellcast_west", o::_w, o::_h, xyipair(0, 0), 50);

    this->addAnimation(8, o::_w * 0, o::_h * 4, "thrust_north", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(8, o::_w * 0, o::_h * 6, "thrust_south", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(8, o::_w * 0, o::_h * 7, "thrust_east", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(8, o::_w * 0, o::_h * 5, "thrust_west", o::_w, o::_h, xyipair(0, 0), 50);

    this->addAnimation(6, o::_w * 0, o::_h * 12, "slash_north", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(6, o::_w * 0, o::_h * 14, "slash_south", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(6, o::_w * 0, o::_h * 15, "slash_east", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(6, o::_w * 0, o::_h * 13, "slash_west", o::_w, o::_h, xyipair(0, 0), 50);

    this->addAnimation(8, o::_w * 3, o::_h * 16, "shoot_north", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(8, o::_w * 3, o::_h * 18, "shoot_south", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(8, o::_w * 3, o::_h * 19, "shoot_east", o::_w, o::_h, xyipair(0, 0), 50);
    this->addAnimation(8, o::_w * 3, o::_h * 17, "shoot_west", o::_w, o::_h, xyipair(0, 0), 50);
}

void Player::animationDone(string animation)
{
    // if (animation.find("walk") == string::npos || )
    {
        this->setAnimationLock(false);
        this->_lockMovement = false;
    }
}

void Player::updateBoundingBox()
{
    this->_boundingBox.update(this->_sprite.x() + 16, this->_sprite.y() + 52, o::_w - 32, 12);
}

void Player::setCurrentLevel(Level *level)
{
    this->_currentLevel = level;
}

Level *Player::getCurrentLevel()
{
    return this->_currentLevel;
}

void Player::moveNorth()
{
    this->_dx = (this->_dx == 0) ? 0 : this->_dx / sqrt(2);
    this->_dy = (this->_dx == 0) ? -o::WALK_SPEED : -o::WALK_SPEED / sqrt(2);
    if (this->_dx == 0)
    {
        this->playAnimation("walk_north");
        this->_facing = direction::NORTH;
    }
}

void Player::moveSouth()
{
    this->_dx = (this->_dx == 0) ? 0 : this->_dx / sqrt(2);
    this->_dy = (this->_dx == 0) ? o::WALK_SPEED : o::WALK_SPEED / sqrt(2);
    if (this->_dx == 0)
    {
        this->playAnimation("walk_south");
        this->_facing = direction::SOUTH;
    }
}

void Player::moveEast()
{
    this->_dx = (this->_dy == 0) ? o::WALK_SPEED : o::WALK_SPEED / sqrt(2);
    this->_dy = (this->_dy == 0) ? 0 : this->_dy / sqrt(2);
    this->playAnimation("walk_east");
    this->_facing = direction::EAST;
}

void Player::moveWest()
{
    this->_dx = (this->_dy == 0) ? -o::WALK_SPEED : -o::WALK_SPEED / sqrt(2);
    this->_dy = (this->_dy == 0) ? 0 : this->_dy / sqrt(2);
    this->playAnimation("walk_west");
    this->_facing = direction::WEST;
}

void Player::stopMoving()
{
    this->_dx = 0;
    this->_dy = 0;
    switch (this->_facing)
    {
    case direction::NORTH:
        this->playAnimation("idle_north");
        break;
    case direction::SOUTH:
        this->playAnimation("idle_south");
        break;
    case direction::EAST:
        this->playAnimation("idle_east");
        break;
    case direction::WEST:
        this->playAnimation("idle_west");
        break;
    }
}

void Player::interact(bool interact)
{
    this->_interact = interact;
}

void Player::attack()
{
    string attackAnimation = "";
    if (this->_inventory->getEquippedWeaponInfo().weaponClass == inv::weapons::Class::SHOOT)
        attackAnimation = "shoot";
    else if (this->_inventory->getEquippedWeaponInfo().weaponClass == inv::weapons::Class::SLASH)
        attackAnimation = "slash";
    else if (this->_inventory->getEquippedWeaponInfo().weaponClass == inv::weapons::Class::THRUST)
        attackAnimation = "thrust";
    else if (this->_inventory->getEquippedWeaponInfo().weaponClass == inv::weapons::Class::SPELLCAST)
        attackAnimation = "spellcast";
    else
        return;

    this->setAnimationLock(false);
    this->_dx = this->_dy = 0;
    switch (this->_facing)
    {
    case direction::NORTH:
        this->playAnimation(attackAnimation + "_north", true, false);
        break;
    case direction::SOUTH:
        this->playAnimation(attackAnimation + "_south", true, false);
        break;
    case direction::EAST:
        this->playAnimation(attackAnimation + "_east", true, false);
        break;
    case direction::WEST:
        this->playAnimation(attackAnimation + "_west", true, false);
        break;
    }
    this->setAnimationLock(true);
    this->_lockMovement = true;
}

void Player::undoMove(float elapsedTime)
{
    this->_sprite.x() -= this->_dx * elapsedTime;
    this->_sprite.y() -= this->_dy * elapsedTime;
    this->updateBoundingBox();
}

void Player::makeMove(float elapsedTime)
{
    if (this->_lockMovement)
        return;

    this->_sprite.x() += this->_dx * elapsedTime;
    this->_sprite.y() += this->_dy * elapsedTime;
    this->updateBoundingBox();
}

void Player::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);
    this->_inventory->update(elapsedTime);

    // Apply Gravity
    if (this->_dy <= o::GRAVITY_CAP && this->_currentLevel->getGravity())
        this->_dy += o::GRAVITY * elapsedTime;

    // Move player by changing x, y by velocity dx, dy
    this->makeMove(elapsedTime);

    this->_dx = this->_dy = 0;
    // Contain Player within Camera.
    this->_sprite.containWithin(*this->_camera);
}

void Player::draw(Graphics &graphics)
{
    this->setRenderableZ(this->getBoundingBox().getBottom());
    AnimatedSprite::draw(graphics, "player");
    this->_inventory->draw(graphics);
}