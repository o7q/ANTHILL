#pragma once

#include "world/particle/particle_handler.hpp"
#include <vector>

class Entity;

struct EntityUpdateContext
{
    const float dt = 0.0f;
    const ParticleHandler &particles;
    const std::vector<const Entity *> &nearbyEntities;
};
