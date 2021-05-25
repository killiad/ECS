#include "../core/Coordinator.h"
#include "../core/Systems.h"
#include "SDL_render.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>

std::shared_ptr<RenderSystem> RegisterRenderSystem(SDL_Renderer* renderer){
    ComponentBitset components;
    auto renderObjSystem = Coordinator::GetInstance().RegisterSystem<RenderSystem>();
    renderObjSystem->setRenderer(renderer);
    components.set(Coordinator::GetInstance().GetComponentType<Drawable>());
    components.set(Coordinator::GetInstance().GetComponentType<Image>());
    components.set(Coordinator::GetInstance().GetComponentType<Transform>());
    Coordinator::GetInstance().SetSystemComponentBitset<RenderSystem>(components);
    return renderObjSystem;
}

std::shared_ptr<PhysicsSystem> RegisterPhysicsSystem(){
    ComponentBitset components;
    auto physicsSystem = Coordinator::GetInstance().RegisterSystem<PhysicsSystem>();
    components.set(Coordinator::GetInstance().GetComponentType<Transform>());
    components.set(Coordinator::GetInstance().GetComponentType<RigidBody>());
    components.set(Coordinator::GetInstance().GetComponentType<Gravity>());
    Coordinator::GetInstance().SetSystemComponentBitset<PhysicsSystem>(components);
    return physicsSystem;
}

std::shared_ptr<InputSystem> RegisterInputSystem(){
    ComponentBitset components;
    auto inputSystem = Coordinator::GetInstance().RegisterSystem<InputSystem>();
    components.set(Coordinator::GetInstance().GetComponentType<Input>());
    Coordinator::GetInstance().SetSystemComponentBitset<InputSystem>(components);
    return inputSystem;
}

std::shared_ptr<MovementSystem> RegisterMovementSystem(){
    ComponentBitset components;
    auto movementSystem = Coordinator::GetInstance().RegisterSystem<MovementSystem>();
    components.set(Coordinator::GetInstance().GetComponentType<Input>());
    components.set(Coordinator::GetInstance().GetComponentType<RigidBody>());
    components.set(Coordinator::GetInstance().GetComponentType<Transform>());
    components.set(Coordinator::GetInstance().GetComponentType<Gravity>());
    components.set(Coordinator::GetInstance().GetComponentType<Movement>());
    Coordinator::GetInstance().SetSystemComponentBitset<MovementSystem>(components);
    return movementSystem;
}
