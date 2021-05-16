#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include <array>
#include <unordered_map>
#include <assert.h>
#include "ECS.h"

class IComponentArray{
    public:
        virtual ~IComponentArray() = default;
        virtual void EntityDestroyed(Entity entity) = 0;
};

template<typename T>
class ComponentArray : public IComponentArray{

    private:
        std::array<T, MAX_ENTITIES> componentArray;
        std::unordered_map<Entity, size_t> entityToIndexMap;
        std::unordered_map<size_t, Entity> indexToEntityMap;
        size_t size;

    public:
        void InsertData(Entity entity, T component){
            assert(entityToIndexMap.find(entity) == entityToIndexMap.end()
                    && "Component added to same entity more than once");

            size_t newIndex = size;
            entityToIndexMap[entity] = newIndex;
            indexToEntityMap[newIndex] = entity;
            componentArray[newIndex] = component;
            ++size;
        }

        void RemoveData(Entity entity){
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end()
                    && "Removing nonexistent component");

            size_t indexOfRemovedEntry = entityToIndexMap[entity];
            size_t indexOfLastElement = size - 1;
            componentArray[indexOfRemovedEntry] = componentArray[indexOfLastElement];

            Entity entityOfLastElement = indexToEntityMap[indexOfLastElement];
            entityToIndexMap[entityOfLastElement] = indexOfRemovedEntry;
            indexToEntityMap[indexOfRemovedEntry] = entityOfLastElement;

            entityToIndexMap.erase(entity);
            indexToEntityMap.erase(indexOfLastElement);
            --size;
        }

        T& GetData(Entity entity){
            assert(entityToIndexMap.find(entity) != entityToIndexMap.end()
                    && "Retrieving nonexistent component");
            return componentArray[entityToIndexMap[entity]];
        }

        void EntityDestroyed(Entity entity) override{
            if(entityToIndexMap.find(entity) != entityToIndexMap.end()){
                RemoveData(entity);
            }
        }
};

#endif
