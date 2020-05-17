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

    Rectangle camera = Rectangle(0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);
    this->_camera = &camera;
    this->_level = Level(graphics, "map1.tmx", xyipair(100, 100), &camera);
    this->_player = Player(graphics, this->_level.getPlayerSpawnPoint() , &camera);
    this->_player.setCurrentLevel(&this->_level);

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
        else if(input.isKeyHeld(SDL_SCANCODE_W))
        {
            this->_player.moveNorth();
        }
        else if(input.isKeyHeld(SDL_SCANCODE_S))
        {
            this->_player.moveSouth();
        }
        else if(input.isKeyHeld(SDL_SCANCODE_A))
        {
            this->_player.moveWest();
        }
        else if(input.isKeyHeld(SDL_SCANCODE_D))
        {
            this->_player.moveEast();
        }
        
        else if(!input.isKeyHeld(SDL_SCANCODE_W) and !input.isKeyHeld(SDL_SCANCODE_S) and 
                !input.isKeyHeld(SDL_SCANCODE_A) and !input.isKeyHeld(SDL_SCANCODE_D))
        {
            this->_player.stopMoving();
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

    this->_level.draw_background(graphics);
    vector<Rectangle> colliding;
    if((colliding = this->_level.checkTileCollision(Rectangle(this->_player.getBoundingBox().getLeft(), this->_player.getSpriteBox().getTop(), 
        this->_player.getBoundingBox().getWidth() - 1,
        abs(this->_player.getBoundingBox().getBottom()-this->_player.getSpriteBox().getTop() - 1 ) ))).size() > 0)
    {
        this->_level.draw_foreground(graphics);
        this->_player.draw(graphics);
    }
    else
    {
        this->_player.draw(graphics);
        this->_level.draw_foreground(graphics);
    }
    
    graphics.flip();
}

void Game::update(float elapsedTime)
{
    this->_player.update(elapsedTime);
    this->_level.update(elapsedTime);

    // Check collisions
    // vector<Rectangle> colliding;
    // if((colliding = this->_level.checkTileCollision(this->_player.getBoundingBox())).size() > 0)
    // {
    //     this->_player.handleTileCollision(colliding);
    // }

    vector<Rectangle> collidingRects = this->_level.checkTileCollision(this->_player.getBoundingBox());
    if(collidingRects.size() > 0)
    {
        this->_player.undoMove(elapsedTime);
    //     this->_player.stopMoving();
            // this->_player.handleTileCollision(collidingRects);
    }

    vector<Slope> collidingSlopes = this->_level.checkSlopeCollision(this->_player.getBoundingBox());
    if(collidingSlopes.size() > 0)
    {
        // cout<<"slope collide"<<endl;
        this->_player.undoMove(elapsedTime);
        // this->_player.stopMoving();
            // this->_player.handleTileCollision(colliding);
    }

    // Change camera coordinates to follow player if no collision is taking place. Camera is centered on player.
    // if(collidingRects.size() == 0 && collidingSlopes.size() == 0)
        this->_camera->setCenter(this->_player.getSpriteBox().getCenter());

    // Contain camera within map. 
    this->_camera->containWithin(Rectangle(0, 0, this->_level.getMapSize().x, this->_level.getMapSize().y));
}
