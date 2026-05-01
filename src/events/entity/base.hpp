#pragma once

#include "events/backend/base.hpp"
#include <cstdint>

enum class EntityEventType
{
    EntityDamage,
    EntitySpawn,
    Particle,
    Backend
};

struct EntityEvent
{
    EntityEvent(const uint64_t caller_, EntityEventType type_) : caller(caller_), type(type_) {}
    virtual ~EntityEvent() = default;

    const uint64_t caller;
    const EntityEventType type;
};
