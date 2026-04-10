#pragma once

#include "world/particle_world/particle_world.hpp"
#include <cstdint>
#include <unordered_map>

class Entity;

struct EntityUpdateContext
{
    const uint64_t id = 0;
    const float dt = 0.0f;
    const ParticleWorld &world;
    const std::unordered_map<uint64_t, const Entity *> &nearbyEntities;
};
