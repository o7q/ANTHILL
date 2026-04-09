#pragma once

#include "events/entity/base.hpp"
#include <memory>

class Entity;

struct EntitySpawnEvent : public EntityEvent
{
    EntitySpawnEvent(const uint64_t caller_)
        : EntityEvent(caller_, EntityEventType::EntitySpawn)
    {
    }

    std::unique_ptr<Entity> entity = nullptr;
};

struct EntityDamageEvent : public EntityEvent
{
    EntityDamageEvent(const uint64_t caller_)
        : EntityEvent(caller_, EntityEventType::EntityDamage)
    {
    }

    uint64_t target = 0;
    float damage = 0.0f;
};
