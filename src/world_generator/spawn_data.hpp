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
    std::function<std::vector<std::unique_ptr<Entity>>(Vec2i, const Assets &)> entities;
    Color backgroundColor;
};
