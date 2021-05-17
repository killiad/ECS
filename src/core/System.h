#ifndef SYSTEM_H
#define SYSTEM_H

#include <set>
#include "ECS.h"
#include "Components.h"

class System{

    public:
        std::set<Entity> entities;
};

#endif
