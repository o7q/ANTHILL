#pragma once

#include <cstdint>

enum class EntityEventType
{
    EntityDamage,
    EntitySpawn,
    ParticleDraw,
    BackendPlaySound
};

struct EntityEvent
{
    EntityEvent(const uint64_t caller_, EntityEventType type_)
        : caller(caller_), type(type_)
    {
    }
    virtual ~EntityEvent() = default;

    const uint64_t caller;
    const EntityEventType type;
};
