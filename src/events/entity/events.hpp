#pragma once

#include "base.hpp"
#include "entity/entity.hpp"
#include "events/scene/base.hpp"

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

struct EntitySceneEvent : public EntityEvent
{

    EntitySceneEvent(const uint64_t caller_, std::unique_ptr<SceneEvent> payload_)
        : EntityEvent(caller_, EntityEventType::Scene), payload(std::move(payload_))
    {
    }

    std::unique_ptr<SceneEvent> payload;
};
