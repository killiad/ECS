#ifndef SYSTEMS_H
#define SYSTEMS_H

#include "System.h"
#include "Coordinator.h"

class PhysicsSystem : public System{
    private:
        double lastUpdate;
    public:
        PhysicsSystem() = default;
        virtual void Update();
};

#endif
