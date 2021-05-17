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
        rigidBody.velocity = rigidBody.velocity + gravity.force * dt;
    }
    lastUpdate = SDL_GetTicks();
}
