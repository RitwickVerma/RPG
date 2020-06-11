#include "animatedtile.h"

AnimatedTile::AnimatedTile(){};

AnimatedTile::AnimatedTile(int ID, xyipair size, xyipair tilesetPosition, xyfpair position, float Z)
    :Tile(NULL, ID, size, tilesetPosition, position, Z)
{
    this->_frameIndex = 0;
}

void AnimatedTile::addTileFrame(animated_tile_frame tileFrame)
{
    this->_frameTiles.push_back(tileFrame);
}

void AnimatedTile::update(float elapsedTime)
{
    this->_timeForUpdate += elapsedTime;
    if(this->_timeForUpdate > this->_frameTiles[this->_frameIndex].frameDuration)
    {
        this->_timeForUpdate -= this->_frameTiles[this->_frameIndex].frameDuration;
        this->_frameIndex++;
    }
    this->_frameIndex %= this->_frameTiles.size();
    
    animated_tile_frame tileFrame = this->_frameTiles[this->_frameIndex];
    this->_tileset = tileFrame.frameTexture;
    this->_tilesetPosition = xyipair(tileFrame.sourceRect.x, tileFrame.sourceRect.y);
    this->_size = xyipair(tileFrame.sourceRect.w, tileFrame.sourceRect.h);
}

void AnimatedTile::draw(Graphics &graphics)
{
    Tile::draw(graphics);
}