#include "level.h"


Level::Level()
{
    MAP_DIR = "content/maps/";
}

Level::Level(Graphics &graphics, string mapName, xyipair spawnPoint, Rectangle *camera):Level()
{
    _mapName=mapName;
    _playerSpawnPoint=spawnPoint;
    _size=xyipair(0,0);
    _camera=camera;
    this->_hasGravity = false;

    this->loadMap(graphics, mapName); 
}

Level::~Level(){}


void Level::update(float elapsedTime)
{ 
    for( auto &p : this->_map)
        visit([&elapsedTime](auto &&arg) { arg.update(elapsedTime); }, p);
}


void Level::draw(Graphics &graphics)
{
    for( auto &p : this->_map)
        visit([&graphics](auto &&arg) { arg.draw(graphics); }, p);
}

vector<Rectangle> Level::checkTileCollision(const Rectangle &other)
{
    vector<Rectangle> collidingRects;
    for(auto &rectangle : this->_collisionRects)
    {
        if(rectangle.collidesWith(other))
            collidingRects.push_back(rectangle);
    }
    return collidingRects;
}

vector<Line> Level::checkLineCollision(const Rectangle &other)
{
    vector<Line> collidingSlopes;
    for(auto &slope : this->_collisionSlopes)
    {
        if(slope.collidesWith(other))
            collidingSlopes.push_back(slope);
    }
    return collidingSlopes;
}

const xyipair Level::getPlayerSpawnPoint() const{
    return this->_playerSpawnPoint;
}