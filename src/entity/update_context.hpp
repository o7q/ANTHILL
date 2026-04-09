#pragma once

#include "world/particle_world/particle_world.hpp"
#include <vector>

class Entity;

struct EntityUpdateContext
{
    const uint64_t id = 0;
    const float dt = 0.0f;
    const ParticleWorld &world;
    const std::vector<const Entity *> &nearbyEntities;
    const Entity *currentPlayer = nullptr;
};
