#ifndef LEVEL_H
#define LEVEL_H

#pragma once

#include "globals.h"
#include "tile.h"
#include "rectangle.h"
#include "slope.h"

struct Graphics;
struct SDL_Texture;
struct Tileset;
class Level
{ 
    public :
        Level();
        Level(Graphics &graphics, string mapName, xyipair spawnPoint, Rectangle *camera = NULL);
        ~Level();
    
        void update(float elapsedTime);
        void draw_background(Graphics &graphics);
        void draw_foreground(Graphics &graphics);
        bool hasGravity() { return this->_hasGravity; }

        xyfpair getOffset() { return _mapOffset; }
        xyipair getMapSize() { return _size; }
        void setOffset(xyfpair offset) { this->_mapOffset = offset; }
        
        void setCamera(Rectangle *camera) { this->_camera = camera; }
        
        vector<Rectangle> checkTileCollision(const Rectangle &other);
        vector<Slope> checkSlopeCollision(const Rectangle &other);
        
        const xyipair getPlayerSpawnPoint() const;

    private:
        string _mapName;
        bool _hasGravity;
        xyipair _playerSpawnPoint;
        xyipair _size;
        Rectangle *_camera;
        // SDL_Texture *_backgroundTexture;
        string MAP_DIR;        

        xyipair _tileSize;
        xyipair _tileCount;
        xyfpair _mapOffset;
        vector<vector<Tile>> _map;
        map<int, Tileset> _tilesets;
        map<int, SDL_Texture*> _tileTextures;
        vector<Rectangle> _collisionRects;
        vector<Slope> _collisionSlopes;

        void loadMap(Graphics &graphics, string mapName);
};

struct Tileset
{
    SDL_Texture *Texture;
    SDL_Surface *Surface;
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
    
    Tileset(SDL_Surface *surface, int first_gid)
    {
        Surface=surface;
        firstGid=first_gid;
    }

};
#endif // !LEVEL_H