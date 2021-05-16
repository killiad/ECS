#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include <memory>
#include <unordered_map>
#include <assert.h>
#include "ECS.h"
#include "System.h"

class SystemManager{

    private:
        std::unordered_map<const char*, ComponentBitset> componentBitsets{};
        std::unordered_map<const char*, std::shared_ptr<System> > systems{};

    public:
        template<typename T>
        std::shared_ptr<T>  RegisterSystem(){
            const char* typeName = typeid(T).name();
            assert(systems.find(typeName) == systems.end() && "Registering system more than once.");

            auto system = std::make_shared<T>();
            systems.insert({typeName, system});
            return system;
        }

        template<typename T>
        void SetComponentBitset(ComponentBitset componentBitset){
            const char* typeName = typeid(T).name();
            assert(systems.find(typeName) != systems.end() && "System used before registered.");

            componentBitsets.insert({typeName, componentBitset});
        }

        void EntityDestroyed(Entity entity){
            for(auto const& pair : systems){
                auto const& system = pair.second;
                system->entities.erase(entity);
            }
        }

        void EntityComponentBitsetChanged(Entity entity, ComponentBitset entityComponents){
            for(auto const& pair : systems){
                auto const& type = pair.first;
                auto const& system = pair.second;
                auto const& systemComponentBitset = componentBitsets[type];

                if((entityComponents & systemComponentBitset) == systemComponentBitset){
                    system->entities.insert(entity);
                }
                else{
                    system->entities.erase(entity);
                }
            }
        }
};

#endif
