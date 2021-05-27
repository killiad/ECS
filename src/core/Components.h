#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>
#include "SDL2/SDL_rect.h"
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_image.h>
#include "Vec2.h"
#include "ECS.h"

//render components
struct Drawable{
    bool draw;
    unsigned int layer;
    double parallax = 1;
    bool wrap_h = false;
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
    Vec2 scale;
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

//input components
struct Input{
    bool keys[284];
};

struct Movement{
    double max_speed;
    double acceleration;
};

#endif
