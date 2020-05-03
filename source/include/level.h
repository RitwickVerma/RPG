#ifndef LEVEL_H

#include "globals.h"

struct Graphics;
struct SDL_Texture;

class Level
{ 
    public :
        Level();
        Level(Graphics &graphics, string mapName, vector2 spawnPoint);
        ~Level();
    
    void update(float elapsedTime);
    void draw(Graphics &graphics);

    private:
        string _mapName;
        vector2 _spawnPoint;
        vector2 _size;
        SDL_Texture *_backgroundTexture;

        void loadMap(Graphics &graphics, string mapName);
};

#endif // !LEVEL_H