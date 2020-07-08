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

    protected:

        void addAnimation(int frames, int x, int y, string animation, int w, int h, xyipair offset, float animationUpdateTime = -1);
        void resetAnimation();
        void stopAnimation();
        void setVisibility(bool visibility);
        bool getVisibility();
        void lockAnimation(bool lock);

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
};

#endif // !1ANIMATEDSPRITE_H