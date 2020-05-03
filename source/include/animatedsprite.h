#ifndef ANIMATEDSPRITE_H
#define ANIMATEDSPRITE_H  

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
        double _timeToUpdate;
        bool _currentAnimationRepeat;
        string _currentAnimation;

        void addAnimation(int frames, int x, int y, string animation, int w, int h, vector2 offset);
        void resetAnimation();
        void stopAnimation();
        void setVisibility(bool visibility);

        virtual void animationDone(string animation) = 0;
        virtual void setupAnimation() = 0;

    private:
        map<string, vector<SDL_Rect>> _animations;
        map<string, vector2> _offsets;

        int _frameIndex;
        double _timeElapsed;
        bool _visible; 
};

#endif // !1ANIMATEDSPRITE_H