#include "../core/Coordinator.h"
#include "../core/Systems.h"
#include "SDL_render.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

void RunGameLoop(){

    const int SCREEN_WIDTH = 640;
    const int SCREEN_HEIGHT = 480;
    std::string game_name = "Game";
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) { 
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl; 
    }

    //Enable gpu_enhanced textures
    IMG_Init(IMG_INIT_PNG);

    TTF_Init();

    auto window = SDL_CreateWindow(game_name.c_str(), 
                               SDL_WINDOWPOS_CENTERED, 
                               SDL_WINDOWPOS_CENTERED, 
                               SCREEN_WIDTH,
                               SCREEN_HEIGHT, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window,-1,0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);

    ComponentBitset components;

    //create render objects system
    auto renderObjSystem = Coordinator::GetInstance().RegisterSystem<RenderObjSystem>();
    renderObjSystem->setRenderer(renderer);
    components.set(Coordinator::GetInstance().GetComponentType<Drawable>());
    components.set(Coordinator::GetInstance().GetComponentType<Image>());
    components.set(Coordinator::GetInstance().GetComponentType<Transform>());
    Coordinator::GetInstance().SetSystemComponentBitset<RenderObjSystem>(components);
    components.reset();

    //create physics system
    auto physicsSystem = Coordinator::GetInstance().RegisterSystem<PhysicsSystem>();
    components.set(Coordinator::GetInstance().GetComponentType<Transform>());
    components.set(Coordinator::GetInstance().GetComponentType<RigidBody>());
    components.set(Coordinator::GetInstance().GetComponentType<Gravity>());
    Coordinator::GetInstance().SetSystemComponentBitset<PhysicsSystem>(components);
    components.reset();


    Entity entity = Coordinator::GetInstance().CreateEntity();
    Coordinator::GetInstance().AddComponent(entity, Gravity{Vec2(0,100)});
    Coordinator::GetInstance().AddComponent(entity, RigidBody{
            .velocity = Vec2::ZERO,
            .acceleration = Vec2::ZERO
            });
    Coordinator::GetInstance().AddComponent(entity, Transform{
            .position = Vec2(100,100),
            .scale = 50,
            .rotation = 0
            });
    Coordinator::GetInstance().AddComponent(entity, Drawable{.draw = true});
    Coordinator::GetInstance().AddComponent(entity, Image{
            .filename = "src/game/GFX/Slime.png",
            .source = SDL_Rect{0,0,32,32},
            .dest = SDL_Rect{100,100,100,100}
            });
    renderObjSystem->Blit(entity);

    while(true){
        auto start_time = SDL_GetTicks();
        SDL_RenderClear(renderer);

        physicsSystem->Update();
        renderObjSystem->Update();
        auto frame_duration = SDL_GetTicks() - start_time;

        SDL_RenderPresent(renderer);
        if (frame_duration < Coordinator::FRAME_DURATION){
            SDL_Delay(Coordinator::FRAME_DURATION - frame_duration);
        }
    }
}
