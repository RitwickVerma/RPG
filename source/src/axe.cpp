#include "axe.h"
#include "graphics.h"
#include "player.h"

namespace o
{
    const string SPRITE_PATH = "axe.png";
}

Axe::Axe(Graphics &graphics, Player *player)
    : Weapon(graphics, player, o::SPRITE_PATH, 0)
{
    this->_player = player;
    // this->_weaponType = inv::weapons::Weapon::BASIC_BOW;
    this->_type = inv::weapons::Weapon::BASIC_AXE;
    this->_class = inv::weapons::Class::SLASH;
}

void Axe::animationDone(string currentAnimation)
{
}

inv::weapons::Weapon Axe::getType()
{
    return this->_type;
}

inv::weapons::Class Axe::getClass()
{
    return this->_class;
}

void Axe::update(float elapsedTime)
{
    Weapon::update(elapsedTime);
}

void Axe::draw(Graphics &graphics)
{
    this->setRenderableZ(this->_player->getRenderableZ() + 0.1);
    Weapon::draw(graphics);
}

// void Bow::setupAnimation()
// {

// }
