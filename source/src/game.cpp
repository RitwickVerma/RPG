#include <SDL2/SDL.h>

#include "game.h"
#include "graphics.h"
#include "input.h"

namespace
{
    const int FPS = 60;
    const int MAX_FRAME_TIME = 6*1000/FPS;
}

Game::Game()
{
    SDL_Init(SDL_INIT_EVERYTHING);
    this->gameLoop();
}
Game::~Game()
{
    
}

void Game::gameLoop()
{
    Graphics graphics;
    SDL_Event event;
    Input input;

    this->_player = AnimatedSprite(graphics, "character.png", 0, 0, 90, 126, 100, 100, 100);
    this->_player.setupAnimation();
    this->_player.playAnimation("walk_north");

    int LAST_TIME_MS = SDL_GetTicks();
    while(true)
    {
        input.beginNewFrame();
        if(SDL_PollEvent(&event)) 
        {
            if(event.type == SDL_KEYDOWN)
            {
                if(event.key.repeat == 0)  
                    input.keyDownEvent(event);
            }
            else if(event.type == SDL_KEYUP)
            {
                input.keyUpEvent(event);
            }
            else if(event.type == SDL_QUIT)
            {
                // SDL_Quit();
                return;
            }
        }
        if(input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
        {
            return;
        }
        
        int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_TIME_MS;
        this->update(std::min(MAX_FRAME_TIME, ELAPSED_TIME_MS));
        LAST_TIME_MS = CURRENT_TIME_MS;

        this->draw(graphics);
    }
}

void Game::draw(Graphics &graphics)
{
    graphics.clear();

    this->_player.draw(graphics, 100, 100);
    
    graphics.flip();
}

void Game::update(float elapsedTime)
{
    this->_player.update(elapsedTime);
}