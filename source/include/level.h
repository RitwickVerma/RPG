#ifndef LEVEL_H
#define LEVEL_H

#pragma once

#include "globals.h"
#include "tile.h"
#include "rectangle.h"

struct Graphics;
struct SDL_Texture;
struct Tileset;
class Level
{ 
    public :
        Level();
        Level(Graphics &graphics, string mapName, xypair spawnPoint);
        ~Level();
    
    void update(float elapsedTime);
    void draw(Graphics &graphics);
    bool hasGravity() { return this->_hasGravity; }
    
    vector<Rectangle> checkTileCollision(const Rectangle &other);
    
    const xypair getPlayerSpawnPoint() const;

    private:
        string _mapName;
        bool _hasGravity;
        xypair _playerSpawnPoint;
        xypair _size;
        // SDL_Texture *_backgroundTexture;
        string MAP_DIR;        

        xypair _tileSize;
        xypair _tileCount;
        vector<Tile> _map;
        map<int, Tileset> _tilesets;
        vector<Rectangle> _collisionRects;

        void loadMap(Graphics &graphics, string mapName);
};

struct Tileset
{
    SDL_Texture *Texture;
    int firstGid;

    Tileset()
    {
        firstGid=-1;
    }

    Tileset(SDL_Texture *texture, int first_gid)
    {
        Texture=texture;
        firstGid=first_gid;
    }

};
#endif // !LEVEL_H