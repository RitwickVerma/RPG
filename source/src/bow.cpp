#include "bow.h"
#include "graphics.h"

namespace o{
    const string SPRITE_PATH = "bow.png";
}

Bow::Bow(Graphics &graphics, Player* player)
    :Weapon(graphics, player, o::SPRITE_PATH, 0)
{ 
    // cout<<"Bow const";
    this->_weaponType = inv::weapon::BASIC_BOW;
}

void Bow::update(float elapsedTime)
{
    Weapon::update(elapsedTime);
}


void Bow::animationDone(string currentAnimation)
{ }

// void Bow::setupAnimation()
// {
    
// }

