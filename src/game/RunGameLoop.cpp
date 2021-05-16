#include "../core/Coordinator.h"
#include "../core/Systems.h"
#include <iostream>

void RunGameLoop(std::vector<std::shared_ptr<System> > systems){

    Entity entity = Coordinator::GetInstance().CreateEntity();
    Coordinator::GetInstance().AddComponent(entity, Gravity{Vec2(0,1)});
    Coordinator::GetInstance().AddComponent(entity, RigidBody{
            .velocity = Vec2::ZERO,
            .acceleration = Vec2::ZERO
            });
    Coordinator::GetInstance().AddComponent(entity, Transform{
            .position = Vec2(100,100),
            .scale = 50,
            .rotation = 0
            });

    while(SDL_GetTicks() < 10000){
        auto start_time = SDL_GetTicks();
        for(auto system : systems){
            system->Update();
            auto frame_duration = SDL_GetTicks() - start_time;
            if (frame_duration < Coordinator::FRAME_DURATION){
                SDL_Delay(Coordinator::FRAME_DURATION - frame_duration);
            }
        }
    }
    Vec2 pos = Coordinator::GetInstance().GetComponent<Transform>(entity).position;
    std::cout << pos.y() << std::endl;
}
