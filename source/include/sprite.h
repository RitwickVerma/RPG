#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "globals.h"

struct Graphics;

class Sprite
{
    public:
        Sprite();
        Sprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY);
        // virtual ~Sprite();
        virtual void update();
        void draw(Graphics &graphics, int x, int y);

    protected:
        SDL_Rect _sourceRect;
        SDL_Texture *_spriteSheet;
        float _x, _y; 

    private:
        string SPRITE_DIR;        
           
};


#endif // !SPRITE_H
