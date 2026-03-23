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
    EntityEvent(const uint64_t caller, EntityEventType type)
        : caller(caller), type(type)
    {
    }
    virtual ~EntityEvent() = default;

    const uint64_t caller;
    const EntityEventType type;
};
