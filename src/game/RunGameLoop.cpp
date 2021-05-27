#include "../core/Coordinator.h"
#include "../core/Systems.h"
#include "SDL_render.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

std::shared_ptr<RenderSystem> RegisterRenderSystem(SDL_Renderer* renderer);
std::shared_ptr<PhysicsSystem> RegisterPhysicsSystem();
std::shared_ptr<InputSystem> RegisterInputSystem();
std::shared_ptr<MovementSystem> RegisterMovementSystem();

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

    auto renderSystem = RegisterRenderSystem(renderer);
    auto physicsSystem = RegisterPhysicsSystem();
    auto inputSystem = RegisterInputSystem(); 
    auto movementSystem = RegisterMovementSystem();

    Entity entity = Coordinator::GetInstance().CreateEntity();
    Coordinator::GetInstance().AddComponent(entity, Gravity{Vec2::ZERO});
    Coordinator::GetInstance().AddComponent(entity, RigidBody{
            .velocity = Vec2::ZERO,
            .acceleration = Vec2::ZERO
            });
    Coordinator::GetInstance().AddComponent(entity, Transform{
            .position = Vec2(100,100),
            .scale = Vec2(1,1),
            .rotation = 0
            });
    Coordinator::GetInstance().AddComponent(entity, Drawable{
            .draw = true,
            .layer = 2
            });
    Coordinator::GetInstance().AddComponent(entity, Image{
            .filename = "src/game/GFX/Slime.png",
            .source = SDL_Rect{0,0,32,32},
            .dest = SDL_Rect{100,100,100,100}
            });
    Coordinator::GetInstance().AddComponent(entity, Input{});
    Coordinator::GetInstance().AddComponent(entity, Movement{.max_speed = 100, .acceleration = 50});
    renderSystem->Blit(entity);
    renderSystem->SetCameraTarget(entity);

    Entity grass = Coordinator::GetInstance().CreateEntity();
    Coordinator::GetInstance().AddComponent(grass, Transform{
            .position = Vec2::ZERO,
            .scale = Vec2(1,1),
            .rotation = 0
            });
    Coordinator::GetInstance().AddComponent(grass, Drawable{
            .draw = true,
            .layer = 1,
            .parallax = .85,
            .wrap_h = true
            });
    Coordinator::GetInstance().AddComponent(grass, Image{
            .filename = "src/game/GFX/grass.png",
            .source = SDL_Rect{0,0,1024,1024},
            .dest = SDL_Rect{0,0,1024,1024}
            });
    renderSystem->Blit(grass);

    while(true){
        auto start_time = SDL_GetTicks();
        SDL_RenderClear(renderer);

        if(!inputSystem->Update()){
            break;
        }
        movementSystem->Update();
        physicsSystem->Update();
        renderSystem->Update();
        auto frame_duration = SDL_GetTicks() - start_time;

        SDL_RenderPresent(renderer);
        if (frame_duration < Coordinator::FRAME_DURATION){
            SDL_Delay(Coordinator::FRAME_DURATION - frame_duration);
        }
    }
}
