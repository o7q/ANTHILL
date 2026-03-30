#pragma once

#include "world/particle/particle_world.hpp"
#include <vector>

class Entity;

struct EntityUpdateContext
{
    const float dt = 0.0f;
    const ParticleWorld &world;
    const std::vector<const Entity *> &nearbyEntities;
};
