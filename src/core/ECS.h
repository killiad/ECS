#ifndef ECS_H
#define ECS_H

#include <cstdio>
#include <bitset>

using Entity = std::size_t;
const Entity MAX_ENTITIES = 5000;

using ComponentType = std::size_t;
const ComponentType MAX_COMPONENTS = 32;
using ComponentBitset = std::bitset<MAX_COMPONENTS>;

#endif
