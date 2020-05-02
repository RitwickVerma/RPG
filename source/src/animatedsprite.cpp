#include "animatedsprite.h"
#include "graphics.h"

AnimatedSprite::AnimatedSprite(){}

AnimatedSprite::AnimatedSprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY, float timeToUpdate)
    :Sprite(graphics, filename, sourceX, sourceY, w, h, posX, posY)
{
    _frameIndex=0;
    _timeToUpdate=timeToUpdate;
    _visible=true;
    _currentAnimationRepeat=false;
    _currentAnimation="";
}

void AnimatedSprite::addAnimation(int frames, int x, int y, string animation, int w, int h, vector2 offset)
{
    for(int i=0; i<frames; i++)
    {
        SDL_Rect tempRect = {(i+x)*w, y, w, h};
        this->_animations[animation].push_back(tempRect);
    }
    this->_offsets[animation]=offset;
}

void AnimatedSprite::resetAnimation()
{
    this->_animations.clear();
    this->_offsets.clear();
}

void AnimatedSprite::playAnimation(string animation, bool repeat)
{
    this->_currentAnimationRepeat=repeat;
    if(this->_currentAnimation != animation)
    {
        this->_currentAnimation = animation;
        this->_frameIndex=0;
    }
}

void AnimatedSprite::setVisibility(bool visibility)
{
    this->_visible=visibility;
}

void AnimatedSprite::stopAnimation()
{
    this->_frameIndex = 0;
    this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::update(int elapsedTime)
{
    Sprite::update();
    this->_timeElapsed += elapsedTime;
    if(this->_timeElapsed > this->_timeToUpdate)
    {
        this->_timeElapsed -= this->_timeToUpdate;
        if(this->_frameIndex < this->_animations[this->_currentAnimation].size()-1)
            this->_frameIndex++;
        else
        {
            if(this->_currentAnimationRepeat == false)
                this->setVisibility(false);
            this->_frameIndex=0;
            this->animationDone(this->_currentAnimation);
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, int x, int y)
{
    if(this->_visible)
    {
        SDL_Rect destRect = {
                                x+this->_offsets[this->_currentAnimation].x,
                                y+this->_offsets[this->_currentAnimation].y,
                                this->_sourceRect.w * globals::SCALING, 
                                this->_sourceRect.h * globals::SCALING 
                            };

        SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];

    // cout<<"in sprite "<<this->_sourceRect.w<<" "<<this->_sourceRect.h;
        // cout<<"source"<<sourceRect.x<<" "<<sourceRect.y<<" "<<sourceRect.w<<" "<<sourceRect.h<<endl;
        // cout<<"dest:"<<destRect.x<<" "<<destRect.y<<" "<<destRect.w<<" "<<destRect.h<<endl;
        graphics.blitSurface(this->_spriteSheet, &sourceRect, &destRect);
    }
}

void AnimatedSprite::animationDone(string animation)
{

}

void AnimatedSprite::setupAnimation()
{
    this->addAnimation(3, 0, 0, "walk_north", 90, 125, vector2(0,0));
}