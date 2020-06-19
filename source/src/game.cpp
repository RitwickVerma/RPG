#include "game.h"
#include "graphics.h"
#include "input.h"

namespace
{
    const int FPS = 60;
    const int MAX_FRAME_TIME = 1000/FPS;
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

    this->_camera = graphics.getCamera();
    this->_level = Level(graphics, "map1.tmx", this->_camera);
    this->_player = Player(graphics, this->_level.getPlayerSpawnPoint() , this->_camera);
    this->_player.setCurrentLevel(&this->_level);
    this->_camera->setCenter(xyfpair(this->_player.getBoundingBox().getCenterX(), this->_player.getBoundingBox().getCenterY()-100));
    this->_hud = HUD(graphics, &this->_player);
    
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

        this->_graphics = graphics;
        this->update(std::min(MAX_FRAME_TIME, ELAPSED_TIME_MS));

        LAST_TIME_MS = CURRENT_TIME_MS;

        this->draw(graphics);
        SDL_Delay(2);
    }
}


void Game::update(float elapsedTime)
{
    this->_player.update(elapsedTime);
    this->_level.update(elapsedTime);

    vector<Rectangle> collidingRects = this->_level.checkTileCollision(this->_player.getBoundingBox());
    if(collidingRects.size() > 0)
    {
        this->_player.handleTileCollision(collidingRects);
    }

    vector<Line> collidingLines = this->_level.checkLineCollision(this->_player.getBoundingBox());
    if(collidingLines.size() > 0)
    {
        this->_player.handleLineCollision(collidingLines, elapsedTime);
    }


    vector<Door> collidingDoors = this->_level.checkDoorCollision(this->_player.getBoundingBox());
    if(collidingDoors.size() > 0)
    {
        this->_player.handleDoorCollision(collidingDoors, this->_level, this->_graphics);
        this->_camera->setCenter(this->_player.getBoundingBox().getCenter());
    }   


    // Camera follows player in a much more natural way which looks animated and super cool.
    float del_x = 0.02*(this->_camera->getCenterX() - this->_player.getBoundingBox().getCenterX());
    float del_y = 0.04*(this->_camera->getCenterY() - this->_player.getBoundingBox().getCenterY());
    del_x = round(del_x*10)/10;
    del_y = round(del_y*10)/10;
    this->_camera->setCenterX( (this->_camera->getCenterX() - del_x));
    this->_camera->setCenterY( (this->_camera->getCenterY() - del_y));

    // Contain camera within map. 
    // this->_camera->containWithin(Rectangle(0, 0, this->_level.getMapSize().x, this->_level.getMapSize().y));

}

void Game::draw(Graphics &graphics)
{
    graphics.clear();

    this->_level.draw(graphics);
    this->_player.draw(graphics);
    graphics.drawQueue();
    this->_hud.draw(graphics);

    graphics.flip();
}