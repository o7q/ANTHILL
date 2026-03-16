#pragma once

#include "entity/entity.hpp"
class Projectile : public Entity
{
  public:
    void update(float dt,
                const std::vector<const Entity *> &nearbyEntities) override
    {
    }
};
