#include "inventory.h"
#include "player.h"
#include "bow.h"


Inventory::Inventory(Graphics &graphics, Player *player):
    _player(player)
{
    // this->_player = player;
    this->_showInventory = false;
    this->_graphics = &graphics;
    this->_currentWeapon = NULL;
    // this->_currentWeapon = new Bow(*this->_graphics, this->_player);   
    this->populateInventory();
}

void Inventory::populateInventory()
{
    this->_allWeapons[inv::weapon::BASIC_BOW] = new Bow(*this->_graphics, this->_player);
}

void Inventory::showInventory(bool show)
{
    this->_showInventory = show;
}

void Inventory::equipWeapon(inv::weapon::Weapons weaponType)
{
    if(weaponType == inv::weapon::BASIC_BOW)
    {
        this->_currentWeapon = this->_allWeapons[weaponType];
    }
    else    this->_currentWeapon = NULL;
}

void Inventory::update(float elapsedTime) 
{
    if(!this->_currentWeapon)   return;

    this->_currentWeapon->update(elapsedTime);
}

void Inventory::draw(Graphics &graphics)
{
    this->drawEquipped(graphics);
}

void Inventory::drawEquipped(Graphics &graphics)
{
    if(this->_currentWeapon)
        this->_currentWeapon->draw(graphics);
}
