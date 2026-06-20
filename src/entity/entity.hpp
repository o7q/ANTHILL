#pragma once

#include "entity/body/entity_body.hpp"
#include "entity/collider/entity_collider.hpp"
#include "entity/metadata.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "px/window/render_command.hpp"

class Entity
{
  public:
    struct DamageSource
    {
        DamageSource(uint64_t afflictor_) : afflictor(afflictor_) {}

        const uint64_t afflictor = 0;
        int amount               = 0;
        px::Vec2i position;
        px::Vec2f direction;
    };

  public:
    Entity(uint64_t parentID = 0) : m_parentID(parentID) {}
    virtual ~Entity() = default;

    virtual void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) = 0;
    virtual void render(const Camera &camera, std::vector<px::RenderCommand> &commandsOut)     = 0;

    void kill() { m_health = 0; }
    virtual void damage(DamageSource source) { m_health -= source.amount; }
    int getHealth() const { return m_health; }

    EntityBody &getBody() { return m_body; }
    const EntityBody &getBody() const { return m_body; }
    EntityCollider &getCollider() { return m_collider; }
    const EntityCollider &getCollider() const { return m_collider; }

    EntityMetadata getMetadata() const { return m_metadata; }

    uint64_t getParent() const { return m_parentID; }

    virtual void onKill(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) const {}

  protected:
    EntityBody m_body;
    EntityCollider m_collider;

    EntityMetadata m_metadata;

    int m_health = 100;

  private:
    const uint64_t m_parentID = 0;
};
