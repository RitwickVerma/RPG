#include "weapon.h"
#include "player.h"

namespace o
{
    const int _w=64;
    const int _h=64;
}

Weapon::Weapon(Graphics &graphics, Player *player, string filename, int damage) :
    _player(player),
    _damage(damage),
    AnimatedSprite(graphics, filename, 0, 0, o::_w, o::_h, 0, 0, 75)
{
    this->setupAnimation();
    this->bindAnimationTo(this->_player);
    this->bindSpritePositionTo(this->_player);
}

// void Weapon::animationDone(string currentAnimation)
// { }

void Weapon::setupAnimation()
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

void Weapon::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);
    // this->playAnimation(this->_player->getCurrentAnimation());
}

void Weapon::draw(Graphics &graphics)
{
    this->setRenderableZ(this->_player->getRenderableZ()+0.1);
    AnimatedSprite::draw(graphics);
}