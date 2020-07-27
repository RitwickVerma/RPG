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
    this->_bindedAnimatedSprite = NULL;
}

void AnimatedSprite::setupStandardAnimations()
{
    // Idle
    this->addAnimation(1, this->getW() * 0, this->getH() * 8, "idle_north", this->getW(), this->getH(), xyipair(0, 0));
    this->addAnimation(1, this->getW() * 0, this->getH() * 10, "idle_south", this->getW(), this->getH(), xyipair(0, 0));
    this->addAnimation(1, this->getW() * 0, this->getH() * 11, "idle_east", this->getW(), this->getH(), xyipair(0, 0));
    this->addAnimation(1, this->getW() * 0, this->getH() * 9, "idle_west", this->getW(), this->getH(), xyipair(0, 0));

    // Walk
    this->addAnimation(9, this->getW() * 0, this->getH() * 8, "walk_north", this->getW(), this->getH(), xyipair(0, 0));
    this->addAnimation(9, this->getW() * 0, this->getH() * 10, "walk_south", this->getW(), this->getH(), xyipair(0, 0));
    this->addAnimation(9, this->getW() * 0, this->getH() * 11, "walk_east", this->getW(), this->getH(), xyipair(0, 0));
    this->addAnimation(9, this->getW() * 0, this->getH() * 9, "walk_west", this->getW(), this->getH(), xyipair(0, 0));

    // Spellcast
    this->addAnimation(7, this->getW() * 0, this->getH() * 0, "spellcast_north", this->getW(), this->getH(), xyipair(0, 0), 75);
    this->addAnimation(7, this->getW() * 0, this->getH() * 2, "spellcast_south", this->getW(), this->getH(), xyipair(0, 0), 75);
    this->addAnimation(7, this->getW() * 0, this->getH() * 3, "spellcast_east", this->getW(), this->getH(), xyipair(0, 0), 75);
    this->addAnimation(7, this->getW() * 0, this->getH() * 1, "spellcast_west", this->getW(), this->getH(), xyipair(0, 0), 75);

    // Thrust
    this->addAnimation(6, this->getW() * 2, this->getH() * 4, "thrust_north", this->getW(), this->getH(), xyipair(0, 0), 75);
    this->addAnimation(6, this->getW() * 2, this->getH() * 6, "thrust_south", this->getW(), this->getH(), xyipair(0, 0), 75);
    this->addAnimation(6, this->getW() * 2, this->getH() * 7, "thrust_east", this->getW(), this->getH(), xyipair(0, 0), 75);
    this->addAnimation(6, this->getW() * 2, this->getH() * 5, "thrust_west", this->getW(), this->getH(), xyipair(0, 0), 75);

    // Slash
    this->addAnimation(6, this->getW() * 0, this->getH() * 12, "slash_north", this->getW(), this->getH(), xyipair(0, 0), 100);
    this->addAnimation(6, this->getW() * 0, this->getH() * 14, "slash_south", this->getW(), this->getH(), xyipair(0, 0), 100);
    this->addAnimation(6, this->getW() * 0, this->getH() * 15, "slash_east", this->getW(), this->getH(), xyipair(0, 0), 100);
    this->addAnimation(6, this->getW() * 0, this->getH() * 13, "slash_west", this->getW(), this->getH(), xyipair(0, 0), 100);

    // Shoot
    this->addAnimation(8, this->getW() * 3, this->getH() * 16, "shoot_north", this->getW(), this->getH(), xyipair(0, 0), 50);
    this->addAnimation(8, this->getW() * 3, this->getH() * 18, "shoot_south", this->getW(), this->getH(), xyipair(0, 0), 50);
    this->addAnimation(8, this->getW() * 3, this->getH() * 19, "shoot_east", this->getW(), this->getH(), xyipair(0, 0), 50);
    this->addAnimation(8, this->getW() * 3, this->getH() * 17, "shoot_west", this->getW(), this->getH(), xyipair(0, 0), 50);
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
    // if(this->_animations.count(animation) == 0)     return;

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

string AnimatedSprite::getCurrentAnimation()
{
    return this->_currentAnimation;
}

void AnimatedSprite::setAnimationLock(bool lock)
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

void AnimatedSprite::bindAnimationTo(AnimatedSprite *animatedSprite)
{
    this->_bindedAnimatedSprite = animatedSprite;
    this->_offsets = this->_bindedAnimatedSprite->getOffsets();
    this->_animationUpdateTimes = this->_bindedAnimatedSprite->getUpdateTimes();
}

void AnimatedSprite::update(float elapsedTime)
{
    Sprite::update();

    if (this->_bindedAnimatedSprite != NULL)
    {
        this->_currentAnimationRepeat = this->_bindedAnimatedSprite->getAnimationRepeat();
        this->_currentAnimation = this->_bindedAnimatedSprite->getCurrentAnimation();
        this->_lockAnimation = this->_bindedAnimatedSprite->getAnimationLock();
        this->_frameIndex = this->_bindedAnimatedSprite->getFrameIndex();
        // return;
        // float _timeForUpdate;
        // bool _visible;
    }

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
    if (this->getVisibility())
    {
        SDL_Rect destRect = {
            this->_sprite.x() + this->_offsets[this->_currentAnimation].x,
            this->_sprite.y() + this->_offsets[this->_currentAnimation].y,
            (int)this->_sprite.w(), (int)this->_sprite.h()};

        SDL_Rect sourceRect = this->_animations[this->_currentAnimation][this->_frameIndex];

        this->makeRenderable(this->getRenderableZ(), this->_spriteSheet, sourceRect, destRect, type);
        graphics.addToRenderQueue(*this);
    }
}
