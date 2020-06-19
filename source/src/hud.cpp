#include "hud.h"
#include "graphics.h"
#include "player.h"

HUD::HUD() {}

HUD::HUD(Graphics &graphics, Player *player)
{
    this->_player = player;
    this->_HUDBegin = Sprite(graphics, "ui.png", 448, 180, 84, 64, 50, 50);
    this->_HUDHealthMid = Sprite(graphics, "ui.png", 532, 184, 9, 16, 134, 54);
    this->_HUDHealthEnd = Sprite(graphics, "ui.png", 550, 182, 33, 20, 134, 52);
    this->_HUDHealthBar = Sprite(graphics, "ui.png", 600, 186, 9, 12, 134, 56);
}

void HUD::update(float elapsedTime){}

void HUD::draw(Graphics &graphics)
{
    this->_HUDBegin.draw(graphics, this->_HUDBegin.getX(), this->_HUDBegin.getY());

    for(int i=0; i<round(this->_player->getMaxHealth())/10; i++)
        this->_HUDHealthMid.draw(graphics, this->_HUDHealthMid.getX() + i*this->_HUDHealthMid.getW(), this->_HUDHealthMid.getY());
    
    this->_HUDHealthEnd.draw(graphics, this->_HUDHealthEnd.getX() + this->_player->getMaxHealth()*this->_HUDHealthMid.getW()/10, this->_HUDHealthEnd.getY());

    for(int i=0; i<round(this->_player->getCurrentHealth()/10); i++)
        this->_HUDHealthBar.draw(graphics, this->_HUDHealthBar.getX() + i*this->_HUDHealthBar.getW(), this->_HUDHealthBar.getY());
}
