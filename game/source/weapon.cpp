#include "weapon.h"
#include "player.h"
// #include "ims.h"

namespace
{
    const int WIDTH = 64;
    const int HEIGHT = 64;
} // namespace

Weapon::Weapon(Graphics &graphics, weapon_info info, Player *player) : _player(player),
                                                                       AnimatedSprite(graphics, info.filename, 0, 0, WIDTH, HEIGHT, 0, 0, 75)
{
    this->_type = info.type;
    this->_class = info.weaponClass;
    this->_info = info;
    this->setupAnimation();
    this->bindAnimationTo(this->_player);
    this->bindSpritePositionTo(this->_player);

    this->_extraWeapon = NULL;
    if (this->_class == inv::weapons::Class::SHOOT)
    {
        weapon_info wp = weapon_info("quiver.png", inv::weapons::Weapon::EXTRA);
        this->_extraWeapon = new Weapon(graphics, wp, this->_player);
    }
}

void Weapon::setupAnimation()
{
    AnimatedSprite::setupStandardAnimations();
}

void Weapon::animationDone(string currentAnimation)
{
}

weapon_info Weapon::getWeaponInfo()
{
    return this->_info;
}

inv::weapons::Weapon Weapon::getType()
{
    return this->_type;
}

inv::weapons::Class Weapon::getClass()
{
    return this->_class;
}

void Weapon::update(float elapsedTime)
{
    if (this->_extraWeapon != NULL)
        this->_extraWeapon->update(elapsedTime);
    AnimatedSprite::update(elapsedTime);
}

void Weapon::draw(Graphics &graphics)
{
    if (this->_extraWeapon != NULL)
    {
        // this->_extraWeapon->setRenderableZ(this->_player->getRenderableZ() - 0.2);
        this->_extraWeapon->draw(graphics);
    }

    this->setRenderableZ(this->_player->getRenderableZ() + ((this->_type == inv::weapons::Weapon::EXTRA) ? -0.1 : 0.1));
    AnimatedSprite::draw(graphics);
}