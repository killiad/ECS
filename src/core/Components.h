#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>
#include "SDL2/SDL_rect.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include "Vec2.h"

//render components
struct Drawable{
    bool draw;
};

struct Image{
    std::string filename;
    SDL_Texture* texture = nullptr;
    SDL_Rect source;
    SDL_Rect dest;
};

struct Animation{
    int num_frames;
    int framerate;
    bool loop;
};

//physics components
struct Transform
{
    Vec2 position;
    double scale;
    double rotation;
};

struct RigidBody
{
    Vec2 velocity;
    Vec2 acceleration;
};

struct Gravity
{
    Vec2 force;
};

#endif
