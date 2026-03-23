#pragma once

#include "event.hpp"
#include <functional>
#include <memory>

class Entity;

struct EntitySpawnEvent : public EntityEvent
{
    EntitySpawnEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::EntitySpawn)
    {
    }

    std::function<std::unique_ptr<Entity>(uint64_t id)> entityFactory;
};

struct EntityDamageEvent : public EntityEvent
{
    EntityDamageEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::EntityDamage)
    {
    }

    uint64_t target = 0;
    int damage = 0;
};
