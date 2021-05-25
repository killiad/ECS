#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <memory>
#include "ECS.h"
#include "EntityManager.h"
#include "ComponentManager.h"
#include "SystemManager.h"

class SystemManager;

class Coordinator{

    private:
        Coordinator() {}
        std::unique_ptr<EntityManager> entityManager;
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<SystemManager> systemManager;

    public:
        static const int FPS = 60;
        static const int FRAME_DURATION = 1000/FPS;
        static const int SCREEN_WIDTH = 640;
        static const int SCREEN_HEIGHT = 480;

        static Coordinator& GetInstance(){
            static Coordinator instance;
            return instance;
        }

        void Init(){
            entityManager = std::make_unique<EntityManager>();
            componentManager = std::make_unique<ComponentManager>();
            systemManager = std::make_unique<SystemManager>();
        }

        Entity CreateEntity(){
            return entityManager->CreateEntity();
        }

        void DestroyEntity(Entity entity){
            entityManager->DestroyEntity(entity);
            componentManager->EntityDestroyed(entity);
            systemManager->EntityDestroyed(entity);
        }

        template<typename T>
        void RegisterComponent(){
            componentManager->RegisterComponent<T>();
        }

        template<typename T>
        void AddComponent(Entity entity, T component){
            componentManager->AddComponent<T>(entity, component);
            
            auto componentBitset = entityManager->GetComponentBitset(entity);
            componentBitset.set(componentManager->GetComponentType<T>(), true);
            entityManager->SetComponentBitset(entity, componentBitset);

            systemManager->EntityComponentBitsetChanged(entity, componentBitset);
        }

        template<typename T>
        void RemoveComponent(Entity entity){
            componentManager->RemoveComponent<T>(entity);

            auto componentBitset = entityManager->GetComponentBitset(entity);
            componentBitset.set(componentManager->GetComponentType<T>(), false);
            entityManager->SetComponentBitset(entity, componentBitset);

            systemManager->EntityComponentBitsetChanged(entity, componentBitset);
        }

        template<typename T>
        T& GetComponent(Entity entity){
            return componentManager->GetComponent<T>(entity);
        }

        template<typename T>
        ComponentType GetComponentType(){
            return componentManager->GetComponentType<T>();
        }

        template<typename T>
        std::shared_ptr<T> RegisterSystem(){
            return systemManager->RegisterSystem<T>();
        }

        template<typename T>
        void SetSystemComponentBitset(ComponentBitset components){
            systemManager->SetComponentBitset<T>(components);
        }
};

#endif
