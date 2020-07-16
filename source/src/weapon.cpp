#include "weapon.h"
#include "player.h"

namespace
{
    const int WIDTH = 64;
    const int HEIGHT = 64;
} // namespace

Weapon::Weapon(Graphics &graphics, Player *player, string filename, int damage) : _player(player),
                                                                                  _damage(damage),
                                                                                  AnimatedSprite(graphics, filename, 0, 0, WIDTH, HEIGHT, 0, 0, 75)
{
    this->setupAnimation();
    this->bindAnimationTo(this->_player);
    this->bindSpritePositionTo(this->_player);
}

// void Weapon::animationDone(string currentAnimation)
// { }

void Weapon::setupAnimation()
{
    this->addAnimation(1, WIDTH * 0, HEIGHT * 8, "idle_north", WIDTH, HEIGHT, xyipair(0, 0));
    this->addAnimation(1, WIDTH * 0, HEIGHT * 10, "idle_south", WIDTH, HEIGHT, xyipair(0, 0));
    this->addAnimation(1, WIDTH * 0, HEIGHT * 11, "idle_east", WIDTH, HEIGHT, xyipair(0, 0));
    this->addAnimation(1, WIDTH * 0, HEIGHT * 9, "idle_west", WIDTH, HEIGHT, xyipair(0, 0));

    this->addAnimation(9, WIDTH * 0, HEIGHT * 8, "walk_north", WIDTH, HEIGHT, xyipair(0, 0));
    this->addAnimation(9, WIDTH * 0, HEIGHT * 10, "walk_south", WIDTH, HEIGHT, xyipair(0, 0));
    this->addAnimation(9, WIDTH * 0, HEIGHT * 11, "walk_east", WIDTH, HEIGHT, xyipair(0, 0));
    this->addAnimation(9, WIDTH * 0, HEIGHT * 9, "walk_west", WIDTH, HEIGHT, xyipair(0, 0));

    this->addAnimation(7, WIDTH * 0, HEIGHT * 0, "spellcast_north", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(7, WIDTH * 0, HEIGHT * 2, "spellcast_south", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(7, WIDTH * 0, HEIGHT * 3, "spellcast_east", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(7, WIDTH * 0, HEIGHT * 1, "spellcast_west", WIDTH, HEIGHT, xyipair(0, 0), 50);

    this->addAnimation(8, WIDTH * 0, HEIGHT * 4, "thrust_north", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(8, WIDTH * 0, HEIGHT * 6, "thrust_south", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(8, WIDTH * 0, HEIGHT * 7, "thrust_east", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(8, WIDTH * 0, HEIGHT * 5, "thrust_west", WIDTH, HEIGHT, xyipair(0, 0), 50);

    this->addAnimation(6, WIDTH * 0, HEIGHT * 12, "slash_north", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(6, WIDTH * 0, HEIGHT * 14, "slash_south", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(6, WIDTH * 0, HEIGHT * 15, "slash_east", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(6, WIDTH * 0, HEIGHT * 13, "slash_west", WIDTH, HEIGHT, xyipair(0, 0), 50);

    this->addAnimation(8, WIDTH * 3, HEIGHT * 16, "shoot_north", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(8, WIDTH * 3, HEIGHT * 18, "shoot_south", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(8, WIDTH * 3, HEIGHT * 19, "shoot_east", WIDTH, HEIGHT, xyipair(0, 0), 50);
    this->addAnimation(8, WIDTH * 3, HEIGHT * 17, "shoot_west", WIDTH, HEIGHT, xyipair(0, 0), 50);
}

void Weapon::update(float elapsedTime)
{
    AnimatedSprite::update(elapsedTime);
}

void Weapon::draw(Graphics &graphics)
{
    AnimatedSprite::draw(graphics);
}