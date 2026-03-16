#pragma once

#include "world/particle/particle_handler.hpp"
#include <vector>

class Entity;

struct EntityUpdateContext
{
    float dt;
    const ParticleHandler &particles;
    const std::vector<const Entity *> &nearbyEntities;
};
