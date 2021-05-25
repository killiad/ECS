#include "Systems.h"
#include <iostream>

RenderSystem::RenderSystem() : renderer(nullptr), camera(Coordinator::GetInstance().CreateEntity()){
    Coordinator::GetInstance().AddComponent(camera, Transform{
            .position = Vec2::ZERO,
            .scale = Vec2(640,480),
            .rotation = 0
            });
}

void RenderSystem::Blit(Entity entity){
    
    auto& image = Coordinator::GetInstance().GetComponent<Image>(entity);
    SDL_Surface* surface = IMG_Load(image.filename.c_str());
    image.texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
}


void RenderSystem::Update(){
    std::map<unsigned int, std::vector<Entity> > entity_layers;
    for(auto const& entity : entities){
        auto& drawable = Coordinator::GetInstance().GetComponent<Drawable>(entity);
        entity_layers[drawable.layer].push_back(entity);
    }

    auto& camera_pos = Coordinator::GetInstance().GetComponent<Transform>(camera);
    SDL_Rect dest;
    for(auto entity_layer : entity_layers){
        for(auto const& entity : entity_layer.second){
            auto& drawable = Coordinator::GetInstance().GetComponent<Drawable>(entity);
            auto& image = Coordinator::GetInstance().GetComponent<Image>(entity);
            auto& transform = Coordinator::GetInstance().GetComponent<Transform>(entity);

            image.dest.x = transform.position.x();
            image.dest.y = transform.position.y();
            dest.x = image.dest.x - drawable.parallax * camera_pos.position.x();
            dest.y = image.dest.y - drawable.parallax * camera_pos.position.y();
            dest.w = transform.scale.x() * image.dest.w;
            dest.h = transform.scale.y() * image.dest.h;
            if(drawable.draw){
                SDL_RenderCopy(renderer, image.texture, &image.source, &dest);
            }
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

        Vec2 vel = Vec2::ZERO;
        if(input.keys[SDL_SCANCODE_W]){
            vel = vel + Vec2::UP;
        }
        if(input.keys[SDL_SCANCODE_A]){
            vel = vel + Vec2::LEFT;
        }
        if(input.keys[SDL_SCANCODE_S]){
            vel = vel + Vec2::DOWN;
        }
        if(input.keys[SDL_SCANCODE_D]){
            vel = vel + Vec2::RIGHT;
        }
        
        rigidBody.velocity = movement.max_speed * vel.getUnitVector();
    }
}
