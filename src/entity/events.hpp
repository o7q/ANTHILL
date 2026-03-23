#pragma once

#include "assets/sound_ids.hpp"
#include "backend/sound/sound_handler.hpp"
#include "world/particle/particle.hpp"
#include <functional>
#include <memory>
#include <vector>

class Entity;

enum class EntityEventType
{
    EntityDamage,
    EntitySpawn,
    WorldModifyDraw,
    PlaySound
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

class EntityEventEmitter
{
  public:
    void emit(std::unique_ptr<EntityEvent> event)
    {
        m_events.push_back(std::move(event));
    }

    const std::vector<std::unique_ptr<EntityEvent>> &getEmittedEvents() const
    {
        return m_events;
    }

    void purge() { m_events.clear(); }

  private:
    std::vector<std::unique_ptr<EntityEvent>> m_events;
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

struct EntityWorldModifyDrawEvent : public EntityEvent
{
    EntityWorldModifyDrawEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::WorldModifyDraw)
    {
    }

    Vec2i pos;
    Particle particle;
    int radius = 5;
};

struct EntitySpawnEvent : public EntityEvent
{
    EntitySpawnEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::EntitySpawn)
    {
    }

    std::function<std::unique_ptr<Entity>(uint64_t id)> entityFactory;
};

struct EntityPlaySoundEvent : public EntityEvent
{
    EntityPlaySoundEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::PlaySound)
    {
    }

    SoundIDKey soundID;
    SoundPlaySettings settings;
};
