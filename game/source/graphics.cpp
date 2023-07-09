#include <SDL2/SDL_image.h>

#include "graphics.h"
#include "utils.h"

Graphics::Graphics()
{
    SDL_CreateWindowAndRenderer(global::SCREEN_WIDTH, global::SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &this->_window, &this->_renderer);
    SDL_SetWindowTitle(this->_window, "Game");
    SDL_RenderSetScale(this->_renderer, global::SCALING_X, global::SCALING_Y);
    // SDL_SetRenderDrawBlendMode(this->_renderer, SDL_BLENDMODE_BLEND);

    this->_camera = Rectangle(0, 0, global::SCREEN_WIDTH, global::SCREEN_HEIGHT);

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

SDL_Texture* Graphics::getTextureFromSurface(SDL_Surface *surface)
{
    if(this->_textures.count(make_pair(surface, xyipair().hash())) != 0)
        return this->_textures[make_pair(surface, xyipair().hash())];

    SDL_Texture *texture = SDL_CreateTextureFromSurface(this->_renderer, surface);
    this->_textures[make_pair(surface, xyipair().hash())] = texture;

    return texture;
}

void Graphics::addToRenderQueue(Renderable renderable)
{
    if( renderable.getRenderableDestRect()->x >= this->_camera.getLeft() - renderable.getRenderableDestRect()->w - 50 && 
        renderable.getRenderableDestRect()->x + renderable.getRenderableDestRect()->w <= this->_camera.getRight() + renderable.getRenderableDestRect()->w + 50 &&
        renderable.getRenderableDestRect()->y >= this->_camera.getTop() - renderable.getRenderableDestRect()->h - 50 && 
        renderable.getRenderableDestRect()->y + renderable.getRenderableDestRect()->h <= this->_camera.getBottom() + renderable.getRenderableDestRect()->h + 50)

    this->_render_queue.push(renderable);
}

void Graphics::drawQueue()
{
    bool playerUnder = false;
    SDL_Rect playerRect;
    while(!this->_render_queue.empty())
    {   
        auto renderable = this->_render_queue.top();

        SDL_SetTextureAlphaMod(renderable.getRenderableTexture(), 255);
        if(playerUnder && utils::checkOverlap(renderable.getRenderableDestRect(), &playerRect) && renderable.getRenderableType() == "tree") 
        {    
            float alphaCoffecient = utils::distance(Rectangle(*renderable.getRenderableDestRect()).getCenter(), Rectangle(playerRect).getCenter());
            alphaCoffecient/=100;
            if(alphaCoffecient<=0.3 )   alphaCoffecient = 0.3;
            if(alphaCoffecient >=1.1)   alphaCoffecient = 1.1;
            SDL_SetTextureAlphaMod(renderable.getRenderableTexture(), 200*alphaCoffecient );

        }


        SDL_Rect dest = {int(renderable.getRenderableDestRect()->x - round(this->_camera.x())), int(renderable.getRenderableDestRect()->y - round(this->_camera.y())), renderable.getRenderableDestRect()->w, renderable.getRenderableDestRect()->h};
        this->blitSurface(renderable.getRenderableTexture(), renderable.getRenderableSourceRect(), &dest);

        if(renderable.getRenderableType() == "player")
        {
            playerUnder = true;
            playerRect = *renderable.getRenderableDestRect();
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
    SDL_Rect window = {0, 0, global::SCREEN_WIDTH, global::SCREEN_HEIGHT};

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
    SDL_Rect window = {0, 0, global::SCREEN_WIDTH, global::SCREEN_HEIGHT};
    
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

SDL_Texture* Graphics::makeSingleTexture(vector<SDL_Texture*> textures)
{
    SDL_Texture* auxtexture = SDL_CreateTexture(this->_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, 500, 500);
    //change the target back to the default and then render the aux
    SDL_SetRenderTarget(this->_renderer, auxtexture);

    for(int i=0; i<textures.size(); i++)
    {   
        SDL_RenderCopy(this->_renderer, auxtexture, NULL, NULL);
    }

    SDL_SetRenderTarget(this->_renderer, NULL); //NULL SETS TO DEFAULT
    // this->_textures[make_pair(surface, xyipair().hash())] = auxtexture;
    return auxtexture;
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
