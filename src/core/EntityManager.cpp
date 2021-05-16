#include "EntityManager.h"
#include "ECS.h"

EntityManager::EntityManager() {
    for(Entity entity = 0; entity < MAX_ENTITIES; ++entity){
        availableEntities.push(entity);
    }
}

Entity EntityManager::CreateEntity(){
    assert(livingEntityCount < MAX_ENTITIES && "Too many entities!");

    Entity id = availableEntities.front();
    availableEntities.pop();
    ++livingEntityCount;

    return id;
}

void EntityManager::DestroyEntity(Entity entity){
    assert(entity < MAX_ENTITIES && "Entity out of range.");

    entityComponenents[entity].reset();
    availableEntities.push(entity);
    --livingEntityCount;
}

void EntityManager::SetComponentBitset(Entity entity, ComponentBitset components){
    assert(entity < MAX_ENTITIES && "Entity out of range.");
    entityComponenents[entity] = components;
}

ComponentBitset EntityManager::GetComponentBitset(Entity entity){
    assert(entity < MAX_ENTITIES && "Entity out of range.");
    return entityComponenents[entity];
}
