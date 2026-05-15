#pragma once

#include "events/external/base.hpp"
#include <cstdint>

enum class EntityEventType
{
    EntityDamage,
    EntityKill,
    EntitySpawn,
    Particle,
    External
};

struct EntityEvent
{
    EntityEvent(const uint64_t caller_, EntityEventType type_) : caller(caller_), type(type_) {}
    virtual ~EntityEvent() = default;

    const uint64_t caller;
    const EntityEventType type;
};
