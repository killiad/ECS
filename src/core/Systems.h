#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "System.h"
#include "Coordinator.h"

//Render systems
//Note: RenderSystem is inherited from only
class RenderSystem : public System{
    public:
        void Blit(Entity entity);
        inline void setRenderer(SDL_Renderer* rend) {renderer = rend;};
    protected:
        RenderSystem() = default;
        SDL_Renderer* renderer;
};

class RenderObjSystem : public RenderSystem{
    public:
        RenderObjSystem() = default; 
        void Update();
};

//physics systems
class PhysicsSystem : public System{
    private:
        double lastUpdate;
    public:
        PhysicsSystem() = default;
        void Update();
};

//input systems
class InputSystem : public System{
    public:
        InputSystem() = default;
        bool Update();
};

class MovementSystem : public System{
    public:
        MovementSystem() = default;
        void Update();
};

#endif
