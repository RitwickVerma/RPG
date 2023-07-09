#include "ims.h"
#include "player.h"
// #include "bow.h"
// #include "axe.h"

IMS::IMS(Graphics &graphics, Player *player) : _player(player)
{
    this->_showInventory = false;
    this->_graphics = &graphics;
    this->_currentEquippedWeapon = NULL;
    this->populateInventory();
}

void IMS::populateInventory()
{
    // Weapons
    this->_allWeapons = {
        {inv::weapons::Weapon::NONE, NULL},
        {inv::weapons::Weapon::BASIC_BOW, new Weapon(*this->_graphics, weapon_info("bow.png", inv::weapons::Weapon::BASIC_BOW), this->_player)},
        {inv::weapons::Weapon::BASIC_AXE, new Weapon(*this->_graphics, weapon_info("axe2.png", inv::weapons::Weapon::BASIC_AXE), this->_player)},
        {inv::weapons::Weapon::BASIC_SPEAR, new Weapon(*this->_graphics, weapon_info("spear.png", inv::weapons::Weapon::BASIC_SPEAR), this->_player)}};
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
    return this->_currentEquippedWeapon->getWeaponInfo();
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
