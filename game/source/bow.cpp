// #include "bow.h"
// #include "graphics.h"
// #include "player.h"

// namespace o
// {
//     const string SPRITE_PATH = "bow.png";
// }

// Bow::Bow(Graphics &graphics, Player *player)
//     : Weapon(graphics, player, o::SPRITE_PATH, 0)
// {
//     this->_player = player;
//     // this->_weaponType = inv::weapons::Weapon::BASIC_BOW;
//     this->_type = inv::weapons::Weapon::BASIC_BOW;
//     this->_class = inv::weapons::Class::SHOOT;
// }

// void Bow::animationDone(string currentAnimation)
// {
// }

// void Bow::update(float elapsedTime)
// {
//     Weapon::update(elapsedTime);
// }

// void Bow::draw(Graphics &graphics)
// {
//     this->setRenderableZ(this->_player->getRenderableZ() + 0.1);
//     Weapon::draw(graphics);
// }

// // void Bow::setupAnimation()
// // {

// // }
