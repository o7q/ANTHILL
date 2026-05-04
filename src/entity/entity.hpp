#pragma once

#include "backend/viewport/render_command.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/metadata.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "math/rectangle.hpp"

class Entity
{
  public:
    struct DamageSource
    {
        DamageSource(uint64_t afflictor_) : afflictor(afflictor_) {}

        const uint64_t afflictor = 0;
        float amount             = 0.0f;
        Vec2i position;
        Vec2f direction;
    };

  public:
    Entity(uint64_t parentID = 0) : m_parentID(parentID) {}
    virtual ~Entity() = default;

    virtual void update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut) = 0;
    virtual void render(const Camera &camera, std::vector<RenderCommand> &commandsOut)         = 0;

    void kill() { m_health = -1.0f; }
    virtual void damage(DamageSource source) { m_health -= source.amount; }
    float getHealth() const { return m_health; }

    EntityBody &getBody() { return m_body; }
    const EntityBody &getBody() const { return m_body; }
    StaticGridRectangle &getBoundingBox() { return m_boundingBox; }
    const StaticGridRectangle &getBoundingBox() const { return m_boundingBox; }

    bool pointInside(Vec2i point) const { return m_boundingBox.pointInside(point - m_body.getPosition()); }

    EntityMetadata getMetadata() const { return m_metadata; }

    uint64_t getParent() const { return m_parentID; }

  protected:
    StaticGridRectangle m_boundingBox;
    EntityBody m_body;

    EntityMetadata m_metadata;

    float m_health = 100.0f;

  private:
    const uint64_t m_parentID = 0;
};
