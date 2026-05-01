#pragma once

#include "base.hpp"
#include "entity/entity.hpp"

struct EntitySpawnEvent : public EntityEvent
{
    EntitySpawnEvent(const uint64_t caller_) : EntityEvent(caller_, EntityEventType::EntitySpawn) {}

    std::unique_ptr<Entity> entity = nullptr;
};

struct EntityDamageEvent : public EntityEvent
{
    EntityDamageEvent(const uint64_t caller_) : EntityEvent(caller_, EntityEventType::EntityDamage) {}

    uint64_t target = 0;
    float damage    = 0.0f;
};

struct EntityParticleEvent : public EntityEvent
{

    EntityParticleEvent(const uint64_t caller_, std::unique_ptr<ParticleEvent> payload_)
        : EntityEvent(caller_, EntityEventType::Particle), payload(std::move(payload_))
    {
    }

    std::unique_ptr<ParticleEvent> payload;
};

struct EntityBackendEvent : public EntityEvent
{

    EntityBackendEvent(const uint64_t caller_, std::unique_ptr<BackendEvent> payload_)
        : EntityEvent(caller_, EntityEventType::Backend), payload(std::move(payload_))
    {
    }

    std::unique_ptr<BackendEvent> payload;
};
