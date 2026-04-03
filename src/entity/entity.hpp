#pragma once

#include "backend/viewport/viewport.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/metadata.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/event_emitter.hpp"
#include "math/rectangle.hpp"
#include "world/camera/camera.hpp"

class Entity
{
  public:
    Entity(uint64_t id, uint64_t parentID = 0) : m_id(id), m_parentID(parentID)
    {
    }
    virtual ~Entity() = default;

    virtual void update(const EntityUpdateContext &context) = 0;
    virtual void render(Viewport &viewport, const Camera &camera) = 0;

    void kill() { m_health = -1.0f; }
    void damage(float amount, uint64_t afflictor = 0) { m_health -= amount; }
    float getHealth() const { return m_health; }

    EntityBody &getBody() { return m_body; }
    const EntityBody &getBody() const { return m_body; }
    StaticGridRectangle &getBoundingBox() { return m_boundingBox; }
    const StaticGridRectangle &getBoundingBox() const { return m_boundingBox; }

    EntityMetadata getMetadata() const { return m_metadata; }

    const uint64_t getID() const { return m_id; }
    const uint64_t getParent() const { return m_parentID; }

    EventEmitter<EntityEvent> &getEventEmitter() { return m_eventEmitter; }

  protected:
    StaticGridRectangle m_boundingBox;
    EntityBody m_body;

    EntityMetadata m_metadata;
    EventEmitter<EntityEvent> m_eventEmitter;

  private:
    const uint64_t m_id = 0;
    const uint64_t m_parentID = 0;

    float m_health = 100.0f;
};
