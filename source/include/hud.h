#ifndef HUD_H
#define HUD_H

#include "sprite.h"

struct Player;

class HUD
{
    public:
        HUD();
        HUD(Graphics &graphics, Player *player);
        void update(float elapsedTime);
        void draw(Graphics &graphics);

    private:
        Player *_player;
        Sprite _HUDBegin;
        Sprite _HUDHealthEnd;
        Sprite _HUDHealthMid;
        Sprite _HUDHealthBar;
};

#endif // !HUD_H
