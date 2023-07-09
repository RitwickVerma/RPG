#include "game.h"
#include "graphics.h"

namespace {
const int FPS = 60;
const int MAX_FRAME_TIME = 1000 / FPS;
} // namespace

Game::Game() : m_graphics(), m_kbh,
{
    SDL_Init(SDL_INIT_EVERYTHING);

    Graphics graphics;
    // SDL_Event event;
    // Input input;
    KeyboardHandler kbh;

    this->m_graphics = graphics;
    this->m_graphics.fadeTo("loading");
    this->load_all_maps(graphics);
    this->m_graphics.fadeFrom("loading");

    this->m_camera = graphics.getCamera();

    this->m_level = this->m_all_maps["map1"];

    this->m_player =
        Player(graphics, this->m_level.getPlayerSpawnPoint(), this->m_camera);
    this->m_inventory = IMS(graphics, &this->m_player);
    this->m_player.setCurrentLevel(&this->m_level);
    this->m_player.setInventory(&this->m_inventory);

    this->m_camera->setCenter(
        xyfpair(this->m_player.getBoundingBox().getCenterX(),
                this->m_player.getBoundingBox().getCenterY() - 100));

    this->m_hud = HUD(graphics, &this->m_player);
    this->m_textbox = TextBox(graphics);

    // Start the game loop
    this->game_loop();
}

Game::~Game()
{
    SDL_Quit();
}

void Game::load_all_maps(Graphics& graphics)
{
    vector<string> maps = {"map1", "player_home"};

    for (string& map : maps)
        this->m_all_maps[map] = Level(graphics, map, &this->m_player);
}

void Game::game_loop()
{
    int LAST_TIME_MS = SDL_GetTicks();

    while (true)
    {
        kbh.handle(*this);

        int CURRENT_TIME_MS = SDL_GetTicks();
        int ELAPSED_TIME_MS = CURRENT_TIME_MS - LAST_TIME_MS;

        this->m_graphics = graphics;
        this->update(std::min(MAX_FRAME_TIME, ELAPSED_TIME_MS));

        LAST_TIME_MS = CURRENT_TIME_MS;

        this->draw(graphics);
        SDL_Delay(2);
    }
}

void Game::update(float elapsed_time)
{
    this->m_player.update(elapsed_time);
    this->m_inventory.update(elapsed_time);
    this->m_level.update(elapsed_time);

    vector<Rectangle> collidingRects =
        this->m_level.checkTileCollision(this->m_player.getBoundingBox());
    if (collidingRects.size() > 0)
    {
        this->m_player.handleTileCollision(collidingRects);
    }

    vector<Line> collidingLines =
        this->m_level.checkLineCollision(this->m_player.getBoundingBox());
    if (collidingLines.size() > 0)
    {
        this->m_player.handleLineCollision(collidingLines, elapsed_time);
    }

    vector<Door> collidingDoors =
        this->m_level.checkDoorCollision(this->m_player.getBoundingBox());
    if (collidingDoors.size() > 0)
    {
        this->m_player.handleDoorCollision(collidingDoors, this->m_level,
                                           &this->m_all_maps, this->m_graphics);
    }

    // Camera follows player in a much more natural way which looks animated and super
    // cool.
    float del_x = 0.02 * (this->m_camera->getCenterX() -
                          this->m_player.getBoundingBox().getCenterX());
    float del_y = 0.04 * (this->m_camera->getCenterY() -
                          this->m_player.getBoundingBox().getCenterY());
    del_x = round(del_x * 10) / 10;
    del_y = round(del_y * 10) / 10;
    this->m_camera->setCenterX((this->m_camera->getCenterX() - del_x));
    this->m_camera->setCenterY((this->m_camera->getCenterY() - del_y));

    // Contain camera within map.
    if (this->m_level.getContainCamera())
        this->m_camera->containWithin(
            Rectangle(0, 0, this->m_level.getMapSize().x, this->m_level.getMapSize().y));
    else
        this->m_camera->setCenter(
            xyfpair(this->m_level.getMapSize().x / 2, this->m_level.getMapSize().y / 2));
}

void Game::draw(Graphics& graphics)
{
    graphics.clear();

    this->m_level.draw(graphics);
    this->m_player.draw(graphics);
    this->m_inventory.draw(graphics);
    graphics.drawQueue();
    this->m_hud.draw(graphics);
    this->m_textbox.draw(graphics);

    graphics.flip();
}
