#pragma once

#include "entity/entity.hpp"
#include "world/particle_handler/particle.hpp"
#include <memory>

struct TerrainGenerateResult
{
    Particle particle;
    std::unique_ptr<Entity> spawnEntity;
};

struct StructureGenerateResult
{
    Particle particle;
    bool overwriteTerrainParticle = false;
};
