#ifndef LEVEL_H
#define LEVEL_H

#pragma once

#include "globals.h"
#include "animatedtile.h"
#include "rectangle.h"
#include "line.h"
#include "thing.h"
#include "door.h"
#include "graphics.h"

struct SDL_Texture;
struct Tileset;
struct Thing;
struct Line;
struct Tile;
class Level
{ 
    public :
        Level();
        Level(Graphics &graphics, string mapName, Rectangle *camera = NULL);
        ~Level();
    
        void update(float elapsedTime);
        void draw(Graphics &graphics);
        bool getGravity() { return this->_hasGravity; }
        bool getContainCamera() { return this->_contain_camera; }

        xyfpair getOffset() { return _mapOffset; }
        xyipair getMapSize() { return _size; }
        vector<Door> getDoors() { return this->_doorRects; }
        string getMapName() { return this->_mapName; }
        
        void setOffset(xyfpair offset) { this->_mapOffset = offset; }
        
        void setCamera(Rectangle *camera) { this->_camera = camera; }
        
        vector<Rectangle> checkTileCollision(const Rectangle &other);
        vector<Line> checkLineCollision(const Rectangle &other);
        vector<Door> checkDoorCollision(const Rectangle &other);

        const xyipair getPlayerSpawnPoint() const;

    private:
        string _mapName;
        bool _hasGravity;
        bool _contain_camera;
        xyipair _playerSpawnPoint;
        xyipair _size;
        Rectangle *_camera;
        // SDL_Texture *_backgroundTexture;
        string MAP_DIR;        

        xyipair _mapTileSize;
        xyipair _tileCount;
        xyfpair _mapOffset;
        vector<variant<Tile, AnimatedTile, Thing>> _map;
        map<int, Tileset> _tilesets;
        map<int, SDL_Texture*> _tileTextures;
        vector<Rectangle> _collisionRects;
        vector<Line> _collisionSlopes;
        vector<Door> _doorRects;

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