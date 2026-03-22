#pragma once

#include "world/particle/particle.hpp"
#include <functional>
#include <memory>
#include <vector>

class Entity;

enum class EntityEventType
{
    EntityDamage,
    EntitySpawn,
    WorldModifyDraw
};

struct EntityEvent
{
    EntityEvent(Entity *const caller, EntityEventType type)
        : caller(caller), type(type)
    {
    }
    virtual ~EntityEvent() = default;

    Entity *const caller = nullptr;
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
    EntityDamageEvent(Entity *const caller)
        : EntityEvent(caller, EntityEventType::EntityDamage)
    {
    }

    Entity *target = nullptr;
    int damage = 0;
};

struct EntityWorldModifyDrawEvent : public EntityEvent
{
    EntityWorldModifyDrawEvent(Entity *const caller)
        : EntityEvent(caller, EntityEventType::WorldModifyDraw)
    {
    }

    Vec2<int> pos;
    Particle particle;
    int radius = 5;
};

struct EntitySpawnEvent : public EntityEvent
{
    EntitySpawnEvent(Entity *const caller)
        : EntityEvent(caller, EntityEventType::EntitySpawn)
    {
    }

    std::function<std::unique_ptr<Entity>(uint64_t id)> entityFactory;
};
