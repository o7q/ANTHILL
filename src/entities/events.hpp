#pragma once

#include "world/particle/particle.hpp"
#include <memory>
#include <vector>

class Entity;

enum class EntityEventType
{
    EntityDamage,
    WorldModify,
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

struct EntityWorldModifyEvent : public EntityEvent
{
    EntityWorldModifyEvent(Entity *const caller,
                           EntityEventType type = EntityEventType::WorldModify)
        : EntityEvent(caller, type)
    {
    }
    virtual ~EntityWorldModifyEvent() = default;

    Vec2<int> pos;
};

struct EntityWorldModifyDrawEvent : public EntityWorldModifyEvent
{
    EntityWorldModifyDrawEvent(Entity *const caller)
        : EntityWorldModifyEvent(caller, EntityEventType::WorldModifyDraw)
    {
    }

    Particle particle;
    int radius = 0;
};
