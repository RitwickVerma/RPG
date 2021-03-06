#ifndef PLAYER_H
#define PLAYER_H

#pragma once

#include "animatedsprite.h"
#include "level.h"
#include "rectangle.h"
// #include "inventory.h"

struct Graphics;
struct IMS;
class Player : public AnimatedSprite
{
public:
    Player();
    Player(Graphics &graphics, xyipair spawnPoint, Rectangle *camera = NULL);
    void draw(Graphics &graphics);
    void update(float elapsedTime);

    void moveNorth();
    void moveSouth();
    void moveEast();
    void moveWest();
    void stopMoving();
    void interact(bool interact = true);
    void attack();

    virtual void animationDone(string currentAnimation);
    virtual void setupAnimation();

    void setCamera(Rectangle *camera) { this->_camera = camera; }
    void setCurrentLevel(Level *level);
    void setInventory(IMS *inventory) { this->_inventory = inventory; }

    void handleTileCollision(vector<Rectangle> &colliding);
    bool handleLineCollision(vector<Line> &colliding, int elapsedTime = 1);
    void handleDoorCollision(vector<Door> &colliding, Level &level, unordered_map<string, Level> *allMaps, Graphics &graphics);

    void undoMove(float elapsedTime);
    void makeMove(float elapsedTime);
    void updateBoundingBox();

    const float getMaxHealth() const { return this->_maxHealth; }
    const float getCurrentHealth() const { return this->_currentHealth; }
    Level *getCurrentLevel();

private:
    float _dx, _dy;
    direction::Direction _facing;
    Level *_currentLevel;
    IMS *_inventory;
    Rectangle *_camera;
    bool _lockMovement;
    bool _grounded;
    bool _interact;
    int _maxHealth;
    int _currentHealth;
};

#endif // !1P PLAYER_H