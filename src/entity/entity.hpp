#pragma once

#include "backend/viewport/viewport.hpp"
#include "entities/events.hpp"
#include "entities/metadata.hpp"
#include "entity/interaction/interaction_box.hpp"
#include "entity/kinetic_body/kinetic_body.hpp"
#include "entity/update_context.hpp"
#include "world/camera/camera.hpp"

class Entity
{
  public:
    Entity(EntityType type = EntityType::Generic) { m_metadata.type = type; }
    virtual ~Entity() = default;

    virtual void update(EntityUpdateContext &context) = 0;
    virtual void render(Viewport &viewport, const Camera &camera) = 0;

    void kill() { m_dead = true; }
    void damage(float amount) { m_health -= amount; }
    bool isDead() const { return m_dead; }

    KineticBody &getBody() { return m_body; }
    const KineticBody &getBody() const { return m_body; }
    const InteractionBox &getInteractionBox() const { return m_interactionBox; }
    EntityMetadata getMetadata() const { return m_metadata; }

    const Entity *const getParent() const { return p_parent; }
    void setParent(const Entity *parent) { p_parent = parent; }
    void clearParent() { p_parent = nullptr; }

  protected:
    virtual void updateMotion(EntityUpdateContext &context);
    virtual void updateHealth()
    {
        if (m_health <= 0.0f)
        {
            kill();
        }
    }
    virtual void updateEvents() { m_eventEmitter.purge(); }

    void renderDebug_boundingBox(Viewport &viewport, const Camera &camera,
                                 Color color = Color(43, 255, 223));

  private:
    void updateApplyExternalMotion(EntityUpdateContext &context);

    Vec2<int> updateMotion_step(Vec2<int> currentPos, Vec2<float> velocity,
                                EntityUpdateContext &context);
    void
    updateMotion_moveAndPreventWorldCollision(Vec2<int> currentPos,
                                              EntityUpdateContext &context);

    const EntityEventEmitter &getEventEmitter() const { return m_eventEmitter; }

  protected:
    InteractionBox m_interactionBox;
    KineticBody m_body;

    EntityMetadata m_metadata;
    EntityEventEmitter m_eventEmitter;

  private:
    const Entity *p_parent = nullptr;

    float m_health = 100.0f;
    bool m_dead = false;
};
