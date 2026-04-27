#pragma once

#include "entity/entity.hpp"
#include "world/particle_handler/particle.hpp"
#include <memory>

struct GenerateResult
{
    Particle particle;
    std::unique_ptr<Entity> spawnEntity;
};
