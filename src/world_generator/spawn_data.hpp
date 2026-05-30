#pragma once

#include "world/particle_handler/particle.hpp"
#include <functional>
#include <memory>
#include <vector>

class Entity;
class Assets;

struct PositionalSpawnData
{
    Particle particle;
    Color backgroundColor;
    std::function<std::vector<std::unique_ptr<Entity>>(Vec2i, const Assets &)> entities;
};

struct StructurePositionalSpawnData : public PositionalSpawnData
{
    bool overwriteTerrainParticle   = false;
    bool overwriteTerrainBackground = false;
    bool overwriteTerrainEntities   = false;
};
