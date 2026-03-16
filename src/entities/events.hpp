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
    EntityEvent(EntityEventType type) : type(type) {}
    virtual ~EntityEvent() = default;

    Entity *caller = nullptr;
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
    EntityDamageEvent() : EntityEvent(EntityEventType::EntityDamage) {}

    Entity *target = nullptr;
    int damage = 0;
};

struct EntityWorldModifyEvent : public EntityEvent
{
    EntityWorldModifyEvent(EntityEventType type = EntityEventType::WorldModify)
        : EntityEvent(type)
    {
    }
    virtual ~EntityWorldModifyEvent() = default;

    Vec2<int> pos;
};

struct EntityWorldModifyDrawEvent : public EntityWorldModifyEvent
{
    EntityWorldModifyDrawEvent()
        : EntityWorldModifyEvent(EntityEventType::WorldModifyDraw)
    {
    }

    Particle particle;
    int radius = 0;
};
