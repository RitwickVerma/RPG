#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

struct Graphics;

class Sprite
{
    public:
        Sprite();
        Sprite(Graphics &graphics, std::string filename, int sourceX, int sourceY, int w, int h, float posX, float posY);
        // virtual ~Sprite();
        // virtual void update();
        void draw(Graphics &graphics, int x, int y);

    private:
        SDL_Rect _sourceRect;
        SDL_Texture *_spriteSheet;
        std::string SPRITE_DIR;        
        float _x, _y;    
};


#endif // !SPRITE_H
