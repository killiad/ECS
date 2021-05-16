#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <queue>
#include <array>
#include <assert.h>
#include "ECS.h"

class EntityManager {

    private:
        std::queue<Entity> availableEntities{};
        std::array<ComponentBitset, MAX_ENTITIES> entityComponenents{};
        size_t livingEntityCount{};

    public:
        EntityManager();
        Entity CreateEntity();
        void DestroyEntity(Entity entity);
        void SetComponentBitset(Entity entity, ComponentBitset components);
        ComponentBitset GetComponentBitset(Entity entity);
};

#endif
