#include "level.h"

Level::Level()
{
    MAP_DIR = "content/maps/";
}

Level::Level(Graphics &graphics, string mapName, Player *player, Rectangle *camera) : Level()
{
    _mapName = mapName;
    _playerSpawnPoint = xyipair(100, 100);
    _size = xyipair(0, 0);
    _player = player;
    _camera = camera;
    this->_hasGravity = false;
    this->_contain_camera = true;

    // graphics.fadeToBlack();
    this->loadMap(graphics, mapName);
    // graphics.fadeFromBlack();
}

Level::~Level()
{
}

void Level::update(float elapsedTime)
{
    for (auto &p : this->_map)
        visit([&elapsedTime](auto &&arg) { arg.update(elapsedTime); }, p);
}

void Level::draw(Graphics &graphics)
{
    for (auto &p : this->_map)
        visit([&graphics](auto &&arg) { arg.draw(graphics); }, p);
}

vector<Rectangle> Level::checkTileCollision(const Rectangle &other)
{
    vector<Rectangle> collidingRects;
    for (auto &rectangle : this->_collisionRects)
    {
        if (rectangle.collidesWith(other))
            collidingRects.push_back(rectangle);
    }
    return collidingRects;
}

vector<Line> Level::checkLineCollision(const Rectangle &other)
{
    vector<Line> collidingSlopes;
    for (auto &slope : this->_collisionSlopes)
    {
        if (slope.collidesWith(other))
            collidingSlopes.push_back(slope);
    }
    return collidingSlopes;
}

vector<Door> Level::checkDoorCollision(const Rectangle &other)
{
    vector<Door> collidingDoors;
    for (auto &door : this->_doorRects)
    {
        if (door.collidesWith(other))
            collidingDoors.push_back(door);
    }
    return collidingDoors;
}

vector<SignPost> Level::checkSignPostCollision(const Rectangle &other)
{
    vector<SignPost> collidingSignPosts;
    for (auto &signPost : this->_signPostRects)
    {
        if (signPost.collidesWith(other))
            collidingSignPosts.push_back(signPost);
    }
    return collidingSignPosts;
}

const xyipair Level::getPlayerSpawnPoint() const
{
    return this->_playerSpawnPoint;
}