#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H

#pragma once

#include "sprite.h"

class AnimatedSprite : public Sprite
{
public:
    AnimatedSprite();
    AnimatedSprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY, float timeToUpdate);

    void playAnimation(string animation, bool restart = false, bool repeat = true);
    void update(float elapsedTime);
    void draw(Graphics &graphics, string type = "");

    void bindAnimationTo(AnimatedSprite *);

    void setAnimationLock(bool lock);

    unordered_map<string, xyipair> getOffsets() { return this->_offsets; }
    unordered_map<string, float> getUpdateTimes() { return this->_animationUpdateTimes; }
    bool getAnimationLock() { return this->_lockAnimation; }
    bool getAnimationRepeat() { return this->_currentAnimationRepeat; }
    int getFrameIndex() { return this->_frameIndex; }

    string getCurrentAnimation();

protected:
    void addAnimation(int frames, int x, int y, string animation, int w, int h, xyipair offset, float animationUpdateTime = -1);
    void resetAnimation();
    void stopAnimation();
    void setVisibility(bool visibility);
    bool getVisibility();
    void setupStandardAnimations();

    virtual void animationDone(string animation) = 0;
    virtual void setupAnimation() = 0;

private:
    float _updateDuration;
    bool _currentAnimationRepeat;
    string _currentAnimation;
    bool _lockAnimation;

    unordered_map<string, vector<SDL_Rect>> _animations;
    unordered_map<string, float> _animationUpdateTimes;
    unordered_map<string, xyipair> _offsets;

    int _frameIndex;
    float _timeForUpdate;
    bool _visible;

    AnimatedSprite *_bindedAnimatedSprite;
};

#endif // !1ANIMATEDSPRITE_H