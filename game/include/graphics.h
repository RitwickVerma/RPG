#pragma once

#include "globals.h"
#include "renderable.h"
#include "rectangle.h"

class Graphics
{
public:
    Graphics();
    ~Graphics();

    // Non-copyable class
    Graphics(const Graphics&) = delete;
    Graphics& operator=(Graphics&) = delete;

    SDL_Surface *loadImage(string &filename);

    /* Renders sourceRect from texture source to destRect on rendering target (window) */
    void blitSurface(SDL_Texture *source, SDL_Rect *sourceRect, SDL_Rect *destRect);

    /* Returns part of a surface from a bigger surface */
    SDL_Surface *getSurfaceFromRect(SDL_Surface *surface, xyipair pos, xyipair size);

    /* Returns a texture from part of a surface (calls getSurfaceFromRect) */
    SDL_Texture *getTextureFromSurfaceRect(SDL_Surface *surface, xyipair pos, xyipair size);

    SDL_Texture *getTextureFromSurface(SDL_Surface *surface);

    void addToRenderQueue(Renderable renderable);

    void drawQueue();

    /* Updates the screen with rendering performed since previous call */
    void flip();

    /* Clear Rendering Target */
    void clear();

    /* Returns instance of Renderer */
    SDL_Renderer *getRenderer();

    void fadeTo(string filename = "black");

    void fadeFrom(string filename = "black");

    SDL_Texture *makeSingleTexture(vector<SDL_Texture *>);

    Rectangle *getCamera();

    struct sort_by_z
    {
        bool operator()(Renderable &a, Renderable &b)
        {
            if (a.getRenderableZ() == b.getRenderableZ())
                return a.getRenderableDestRect()->x > b.getRenderableDestRect()->x;
            return a.getRenderableZ() > b.getRenderableZ();
        }
    };

    struct hash_pair
    {
        template <class T1, class T2>
        size_t operator()(const pair<T1, T2> &p) const
        {
            auto hash1 = hash<T1>{}(p.first);
            auto hash2 = hash<T2>{}(p.second);
            return hash1 ^ hash2;
        }
    };

private:
    SDL_Window *_window;
    SDL_Renderer *_renderer;
    Rectangle _camera;

    priority_queue<Renderable, vector<Renderable>, sort_by_z> _render_queue;
    unordered_map<string, SDL_Surface *> _surfaces;
    unordered_map<pair<SDL_Surface *, long>, SDL_Texture *, hash_pair> _textures;
};