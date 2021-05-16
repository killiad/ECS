#include "../core/ECS.h"
#include "../core/Coordinator.h"
#include "../core/Components.h"
#include "../core/Systems.h"

std::vector<std::shared_ptr<System> > RegisterSystems(){

    std::vector<std::shared_ptr<System> > systems;

    //create physics system
    auto physicsSystem = Coordinator::GetInstance().RegisterSystem<PhysicsSystem>();
    ComponentBitset physicsComponents;
    physicsComponents.set(Coordinator::GetInstance().GetComponentType<Transform>());
    physicsComponents.set(Coordinator::GetInstance().GetComponentType<RigidBody>());
    physicsComponents.set(Coordinator::GetInstance().GetComponentType<Gravity>());
    Coordinator::GetInstance().SetSystemComponentBitset<PhysicsSystem>(physicsComponents);
    systems.push_back(physicsSystem);

    return systems;
}
