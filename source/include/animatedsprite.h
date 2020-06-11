#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H  

#pragma once

#include "sprite.h"

class AnimatedSprite : public Sprite
{
    public:
        AnimatedSprite();
        AnimatedSprite(Graphics &graphics, string filename, int sourceX, int sourceY, int w, int h, float posX, float posY, float timeToUpdate);

        void playAnimation(string animation, bool repeat = true);
        void update(float elapsedTime);

        void draw(Graphics &graphics, int x, int y);


    
    protected:
        float _updateDuration;
        bool _currentAnimationRepeat;
        string _currentAnimation;

        void addAnimation(int frames, int x, int y, string animation, int w, int h, xyipair offset);
        void resetAnimation();
        void stopAnimation();
        void setVisibility(bool visibility);

        virtual void animationDone(string animation) = 0;
        virtual void setupAnimation() = 0;

    private:
        map<string, vector<SDL_Rect>> _animations;
        map<string, xyipair> _offsets;

        int _frameIndex;
        float _timeForUpdate;
        bool _visible; 
};

#endif // !1ANIMATEDSPRITE_H