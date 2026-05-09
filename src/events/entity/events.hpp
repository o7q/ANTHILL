#pragma once

#include "base.hpp"
#include "entity/entity.hpp"
#include "events/external/base.hpp"

struct EntitySpawnEvent : public EntityEvent
{
    EntitySpawnEvent(const uint64_t caller_) : EntityEvent(caller_, EntityEventType::EntitySpawn) {}

    std::unique_ptr<Entity> entity = nullptr;
};

struct EntityDamageEvent : public EntityEvent
{
    EntityDamageEvent(const uint64_t caller_)
        : EntityEvent(caller_, EntityEventType::EntityDamage), source(caller_)
    {
    }

    Entity::DamageSource source;
    uint64_t target = 0;
};

struct EntityParticleEvent : public EntityEvent
{

    EntityParticleEvent(const uint64_t caller_, std::unique_ptr<ParticleEvent> payload_)
        : EntityEvent(caller_, EntityEventType::Particle), payload(std::move(payload_))
    {
    }

    std::unique_ptr<ParticleEvent> payload;
};

struct EntityExternalEvent : public EntityEvent
{

    EntityExternalEvent(const uint64_t caller_, std::unique_ptr<ExternalEvent> payload_)
        : EntityEvent(caller_, EntityEventType::External), payload(std::move(payload_))
    {
    }

    std::unique_ptr<ExternalEvent> payload;
};
