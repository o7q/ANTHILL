#pragma once

#include "backend/time/time_handler.hpp"
#include "world/particle_handler/particle_handler.hpp"
#include <cstdint>
#include <unordered_map>

class Entity;

struct EntityUpdateContext
{
    const uint64_t id = 0;
    const TimeInfo time;
    const ParticleHandler &particleHandler;
    const std::unordered_map<uint64_t, const Entity *> &nearbyEntities;
};
