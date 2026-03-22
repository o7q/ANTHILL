#pragma once

#include "backend/viewport/viewport.hpp"
#include "entity/events.hpp"
#include "entity/interaction/interaction_box.hpp"
#include "entity/kinetic_body/kinetic_body.hpp"
#include "entity/metadata.hpp"
#include "entity/update_context.hpp"
#include "world/camera/camera.hpp"

class Entity
{
  public:
    Entity(uint64_t id, EntityType type = EntityType::Generic) : m_id(id)
    {
        m_metadata.type = type;
    }
    virtual ~Entity() = default;

    virtual void update(const EntityUpdateContext &context) = 0;
    virtual void render(Viewport &viewport, const Camera &camera) = 0;

    void kill() { m_dead = true; }
    void damage(float amount, const Entity *afflictor = nullptr)
    {
        m_health -= amount;
    }
    bool isDead() const { return m_dead; }

    KineticBody &getBody() { return m_body; }
    const KineticBody &getBody() const { return m_body; }
    const InteractionBox &getInteractionBox() const { return m_interactionBox; }
    EntityMetadata getMetadata() const { return m_metadata; }

    const uint64_t getParent() const { return m_parentID; }
    void setParent(uint64_t id) { m_parentID = id; }
    void clearParent() { m_parentID = 0; }

    EntityEventEmitter &getEventEmitter() { return m_eventEmitter; }

    uint64_t getID() const { return m_id; }

  protected:
    virtual void updateMotion(const EntityUpdateContext &context);
    virtual void updateHealth()
    {
        if (m_health <= 0.0f)
        {
            kill();
        }
    }

    void renderDebug_boundingBox(Viewport &viewport, const Camera &camera,
                                 Color color = Color(43, 255, 223));

  private:
    void updateApplyExternalMotion(Vec2<int> currentPos,
                                   const EntityUpdateContext &context);
    void updateMotion_moveAndPreventWorldCollision(
        Vec2<float> currentPos, const EntityUpdateContext &context);

  protected:
    InteractionBox m_interactionBox;
    KineticBody m_body;

    EntityMetadata m_metadata;
    EntityEventEmitter m_eventEmitter;

  private:
    const uint64_t m_id = 0;
    uint64_t m_parentID = 0;

    float m_health = 100.0f;
    bool m_dead = false;
};
