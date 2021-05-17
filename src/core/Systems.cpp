#include "Systems.h"
#include <iostream>

void RenderSystem::Blit(Entity entity){
    
    auto& image = Coordinator::GetInstance().GetComponent<Image>(entity);
    SDL_Surface* surface = IMG_Load(image.filename.c_str());
    image.texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}

void RenderObjSystem::Update(){
    for(auto const& entity : entities){
        auto& drawable = Coordinator::GetInstance().GetComponent<Drawable>(entity);
        auto& image = Coordinator::GetInstance().GetComponent<Image>(entity);
        auto& transform = Coordinator::GetInstance().GetComponent<Transform>(entity);

        image.dest.x = transform.position.x();
        image.dest.y = transform.position.y();
        if(drawable.draw){
            SDL_RenderCopy(renderer, image.texture, &image.source, &image.dest);
        }
    }
}

void PhysicsSystem::Update(){

    //ms to sec
    double dt = (SDL_GetTicks() - lastUpdate) / 1000.0;
    for(auto const& entity : entities){
        auto& transform = Coordinator::GetInstance().GetComponent<Transform>(entity);
        auto& rigidBody = Coordinator::GetInstance().GetComponent<RigidBody>(entity);
        auto& gravity = Coordinator::GetInstance().GetComponent<Gravity>(entity);

        transform.position = transform.position + rigidBody.velocity * dt;
        rigidBody.velocity = rigidBody.velocity + gravity.force * dt + rigidBody.acceleration * dt;
    }
    lastUpdate = SDL_GetTicks();
}

bool InputSystem::Update(){
    SDL_Event event;
    while(SDL_PollEvent(&event) > 0){
        if(event.type == SDL_QUIT){
            return false;
        }
        for(auto const& entity : entities){
            auto keys = Coordinator::GetInstance().GetComponent<Input>(entity).keys;
            switch(event.type){
                case SDL_KEYDOWN:
                    keys[event.key.keysym.scancode] = true;
                    break;
                case SDL_KEYUP:
                    keys[event.key.keysym.scancode] = false;
                    break;
                default:
                    break;
            }
        }
    }
    return true;
}

void MovementSystem::Update(){
    for(auto const& entity : entities){
        auto& rigidBody = Coordinator::GetInstance().GetComponent<RigidBody>(entity);
        auto& input = Coordinator::GetInstance().GetComponent<Input>(entity);
        auto& movement = Coordinator::GetInstance().GetComponent<Movement>(entity);

        Vec2 acc = Vec2::ZERO;
        if(input.keys[SDL_SCANCODE_W]){
            acc = acc + Vec2::UP;
        }
        if(input.keys[SDL_SCANCODE_A]){
            acc = acc + Vec2::LEFT;
        }
        if(input.keys[SDL_SCANCODE_S]){
            acc = acc + Vec2::DOWN;
        }
        if(input.keys[SDL_SCANCODE_D]){
            acc = acc + Vec2::RIGHT;
        }

        if(acc.getLength() > 0){
            if(rigidBody.velocity.getLength() < movement.max_speed){
                acc = movement.acceleration * acc.getUnitVector();
                rigidBody.acceleration = acc;
            }
            else{
                rigidBody.acceleration = 0;
            }
        }
        else{
            rigidBody.acceleration = Vec2::ZERO;
            rigidBody.velocity = Vec2::ZERO;
        }
    }
}
