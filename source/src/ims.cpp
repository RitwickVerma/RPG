#include "ims.h"
#include "player.h"
#include "bow.h"
#include "axe.h"

IMS::IMS(Graphics &graphics, Player *player) : _player(player)
{
    this->_showInventory = false;
    this->_graphics = &graphics;
    this->_currentEquippedWeapon = NULL;
    this->populateInventory();
}

void IMS::populateInventory()
{
    this->_allWeapons[inv::weapons::Weapon::NONE] = NULL;
    this->_allWeapons[inv::weapons::Weapon::BASIC_BOW] = new Bow(*this->_graphics, this->_player);
    this->_allWeapons[inv::weapons::Weapon::BASIC_AXE] = new Axe(*this->_graphics, this->_player);
}

void IMS::showInventory(bool show)
{
    this->_showInventory = show;
}

void IMS::setEquippedWeapon(inv::weapons::Weapon weaponType)
{
    try
    {
        this->_currentEquippedWeapon = this->_allWeapons.at(weaponType);
    }
    catch (std::out_of_range &error)
    {
        this->_currentEquippedWeapon = NULL;
    }
}

weapon_info IMS::getEquippedWeaponInfo()
{
    if (!this->_currentEquippedWeapon)
        return weapon_info();
    return weapon_info(this->_currentEquippedWeapon->getType(), this->_currentEquippedWeapon->getClass());
}

void IMS::update(float elapsedTime)
{
    if (!this->_currentEquippedWeapon)
        return;

    this->_currentEquippedWeapon->update(elapsedTime);
}

void IMS::draw(Graphics &graphics)
{
    this->drawEquipped(graphics);
}

void IMS::drawEquipped(Graphics &graphics)
{
    if (this->_currentEquippedWeapon)
        this->_currentEquippedWeapon->draw(graphics);
}
