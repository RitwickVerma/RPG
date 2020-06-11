#include "animatedsprite.h"
#include "graphics.h"
#include "renderable.h"

AnimatedSprite::AnimatedSprite(){}

AnimatedSprite::AnimatedSprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY, float timeToUpdate)
    :Sprite(graphics, filename, sourceX, sourceY, w, h, posX, posY)
{
    _frameIndex=0;
    _updateDuration=timeToUpdate;
    _visible=true;
    _currentAnimationRepeat=false;
    _currentAnimation="";
}

void AnimatedSprite::addAnimation(int frames, int x, int y, string animation, int w, int h, xyipair offset)
{
    for(int i=0; i<frames; i++)
    {
        SDL_Rect tempRect = {x+(i*w), y, w, h};
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

void AnimatedSprite::update(float elapsedTime)
{
    Sprite::update();
    this->_timeForUpdate += elapsedTime;
    if(this->_timeForUpdate > this->_updateDuration)
    {
        this->_timeForUpdate -= this->_updateDuration;
        if(this->_frameIndex < this->_animations[this->_currentAnimation].size()-1)
            this->_frameIndex++;
        else
        {
            if(this->_currentAnimationRepeat == false)
                this->setVisibility(false);
            this->stopAnimation();
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
                                (int)this->_sprite.w , (int)this->_sprite.h  
                            };

        SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];

        Renderable r = Renderable(this->_boundingBox.getBottom(), this->_spriteSheet, sourceRect, destRect);
        graphics.addToRenderQueue(r);
        // graphics.blitSurface(this->_spriteSheet, &sourceRect, &destRect);
    }
}
