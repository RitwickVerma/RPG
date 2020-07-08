#include "animatedsprite.h"
#include "graphics.h"
#include "renderable.h"

AnimatedSprite::AnimatedSprite() {}

AnimatedSprite::AnimatedSprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY, float timeToUpdate)
    : Sprite(graphics, filename, sourceX, sourceY, w, h, posX, posY)
{
    _frameIndex = 0;
    _updateDuration = timeToUpdate;
    _visible = true;
    _currentAnimationRepeat = false;
    _currentAnimation = "";
    _lockAnimation = false;
}

void AnimatedSprite::addAnimation(int frames, int x, int y, string animation, int w, int h, xyipair offset, float animationUpdateTime)
{
    for (int i = 0; i < frames; i++)
    {
        SDL_Rect tempRect = {x + (i * w), y, w, h};
        this->_animations[animation].push_back(tempRect);
    }
    this->_offsets[animation] = offset;
    this->_animationUpdateTimes[animation] = ((animationUpdateTime == -1) ? this->_updateDuration : animationUpdateTime);
}

void AnimatedSprite::resetAnimation()
{
    this->_animations.clear();
    this->_offsets.clear();
    this->_animationUpdateTimes.clear();
}

void AnimatedSprite::playAnimation(string animation, bool restart, bool repeat)
{
    if (!this->_lockAnimation)
    {
        this->_currentAnimationRepeat = repeat;
        if (this->_currentAnimation != animation)
        {
            this->_currentAnimation = animation;
            this->_frameIndex = 0;
        }
        else if (restart)
            this->_frameIndex = 0;
    }
}

void AnimatedSprite::setVisibility(bool visibility)
{
    this->_visible = visibility;
}

bool AnimatedSprite::getVisibility()
{
    return this->_visible;
}

void AnimatedSprite::lockAnimation(bool lock)
{
    this->_lockAnimation = lock;
}

void AnimatedSprite::stopAnimation()
{
    if (this->_currentAnimationRepeat == true)
        this->_frameIndex = 0;
    else
        this->animationDone(this->_currentAnimation);
}

void AnimatedSprite::update(float elapsedTime)
{
    Sprite::update();
    this->_timeForUpdate += elapsedTime;
    if (this->_timeForUpdate > this->_animationUpdateTimes[this->_currentAnimation])
    {
        this->_timeForUpdate -= this->_animationUpdateTimes[this->_currentAnimation];
        if (this->_frameIndex < this->_animations[this->_currentAnimation].size() - 1)
            this->_frameIndex++;
        else
        {
            // if(this->_currentAnimationRepeat == false)
            // this->setVisibility(false);
            this->stopAnimation();
        }
    }
}

void AnimatedSprite::draw(Graphics &graphics, string type)
{
    if(this->getVisibility())
    {
        SDL_Rect destRect = {
                                this->_sprite.x()+this->_offsets[this->_currentAnimation].x,
                                this->_sprite.y()+this->_offsets[this->_currentAnimation].y,
                                (int)this->_sprite.w() , (int)this->_sprite.h()  
                            };

        SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];

        this->makeRenderable(this->_boundingBox.getBottom(), this->_spriteSheet, sourceRect, destRect, type);
        graphics.addToRenderQueue(*this);
    }
}
