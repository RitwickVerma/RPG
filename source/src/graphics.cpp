#include <SDL2/SDL_image.h>

#include "graphics.h"
#include "utils.h"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Game");
    SDL_RenderSetScale(this->_renderer, globals::SCALING_X, globals::SCALING_Y);
    // SDL_SetRenderDrawBlendMode(this->_renderer, SDL_BLENDMODE_BLEND);

    this->_camera = Rectangle(0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT);

}

Graphics::~Graphics()
{  
    SDL_DestroyWindow(this->_window);
    SDL_DestroyRenderer(this->_renderer);
}

SDL_Surface * Graphics::loadImage(string &filepath)
{
    if(this->_surfaces.count(filepath) == 0)
        this->_surfaces[filepath] = IMG_Load(filepath.c_str());
    return this->_surfaces[filepath];
}

SDL_Surface *Graphics::getSurfaceFromRect(SDL_Surface *surface, xyipair pos, xyipair size)
{
    SDL_LockSurface(surface);
    surface->userdata = (void*)((unsigned*)surface->pixels + pos.y*surface->w + pos.x);
    SDL_UnlockSurface(surface);
    SDL_Surface *newSurface = SDL_CreateRGBSurfaceWithFormatFrom(surface->userdata, size.x, size.y, surface->format->BitsPerPixel, surface->pitch, surface->format->format);
    return newSurface;
}

SDL_Texture* Graphics::getTextureFromSurfaceRect(SDL_Surface *surface, xyipair pos, xyipair size)
{
    if(this->_textures.count(make_pair(surface, pos.hash())) != 0)
        return this->_textures[make_pair(surface, pos.hash())];

    SDL_Surface *newSurface = this->getSurfaceFromRect(surface, pos, size);
    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, newSurface);
    SDL_FreeSurface(newSurface);

    this->_textures[make_pair(surface, pos.hash())] = texture;
    return texture;
}

void Graphics::addToRenderQueue(Renderable renderable)
{
    if( renderable.getDestRect()->x >= this->_camera.getLeft() - renderable.getDestRect()->w - 50 && 
        renderable.getDestRect()->x + renderable.getDestRect()->w <= this->_camera.getRight() + renderable.getDestRect()->w + 50 &&
        renderable.getDestRect()->y >= this->_camera.getTop() - renderable.getDestRect()->h - 50 && 
        renderable.getDestRect()->y + renderable.getDestRect()->h <= this->_camera.getBottom() + renderable.getDestRect()->h + 50)

    this->_render_queue.push(renderable);
}

void Graphics::drawQueue()
{
    bool playerUnder = false;
    SDL_Rect playerRect;
    while(!this->_render_queue.empty())
    {   
        auto renderable = this->_render_queue.top();

        SDL_SetTextureAlphaMod(renderable.getTexture(), 255);
        if(playerUnder && utils::checkOverlap(renderable.getDestRect(), &playerRect) && renderable.getType() == "tree") 
        {    
            float alphaCoffecient = utils::distance(Rectangle(*renderable.getDestRect()).getCenter(), Rectangle(playerRect).getCenter());
            alphaCoffecient/=100;
            if(alphaCoffecient<=0.3 )   alphaCoffecient = 0.3;
            if(alphaCoffecient >=1.1)   alphaCoffecient = 1.1;
            SDL_SetTextureAlphaMod(renderable.getTexture(), 200*alphaCoffecient );

        }


        SDL_Rect dest = {int(renderable.getDestRect()->x - round(this->_camera.x())), int(renderable.getDestRect()->y - round(this->_camera.y())), renderable.getDestRect()->w, renderable.getDestRect()->h};
        this->blitSurface(renderable.getTexture(), renderable.getSourceRect(), &dest);

        if(renderable.getType() == "player")
        {
            playerUnder = true;
            playerRect = *renderable.getDestRect();
        }
        this->_render_queue.pop();
    }
}

void Graphics::blitSurface(SDL_Texture *source, SDL_Rect *sourceRect, SDL_Rect *destRect) 
{
    SDL_RenderCopy(this->_renderer, source, sourceRect, destRect);        
}

void Graphics::fadeTo(string filename)
{
    // this->_fade = true;
    float i;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect window = {0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT};

    string dir = "content/sprites/" + filename + ".png";
    surface = loadImage(dir);
    texture = SDL_CreateTextureFromSurface(this->_renderer, surface);

    for (i=2;i<=255;i+=5) 
    {
        // this->clear();
        SDL_SetTextureAlphaMod(texture, i);
        this->blitSurface(texture, &window, &window);
        this->flip();
        SDL_Delay(10);
    }
}

void Graphics::fadeFrom(string filename)
{
    // this->_fade = true;
    float i;
    SDL_Surface *surface;
    SDL_Texture *texture;
    SDL_Rect window = {0, 0, globals::SCREEN_WIDTH, globals::SCREEN_HEIGHT};
    
    string dir = "content/sprites/" + filename + ".png";
    surface = loadImage(dir);
    texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
    for (i=255;i>=2;i-=5) 
    {
        this->clear();
        SDL_SetTextureAlphaMod(texture, i);
        this->blitSurface(texture, &window, &window);
        this->flip();
        SDL_Delay(5);
    }
}

void Graphics::flip()
{
    SDL_RenderPresent(this->_renderer);
}

void Graphics::clear()
{
    SDL_RenderClear(this->_renderer);
}

SDL_Renderer *Graphics::getRenderer()
{
    return this->_renderer;
}

Rectangle *Graphics::getCamera()
{
    return &this->_camera;
}
