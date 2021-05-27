#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "System.h"
#include "Coordinator.h"
#include <map>

//Render system
class RenderSystem : public System{
    public:
        RenderSystem();
        void Update();
        void Blit(Entity entity);
        void SetCameraTarget(Entity& entity);
        inline void setRenderer(SDL_Renderer* rend) {renderer = rend;};
    private:
        SDL_Renderer* renderer;
        Entity camera;
        Entity* camera_target;
        Vec2 camera_offset;
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
