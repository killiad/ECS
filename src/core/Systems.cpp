#include "Systems.h"

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
