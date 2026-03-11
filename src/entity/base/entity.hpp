#pragma once

#include "backend/viewport.hpp"
#include "entities/metadata.hpp"
#include "entity/base/interaction/entity_interaction_box.hpp"
#include "entity/base/kinetic_body/entity_kinetic_body.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/particle_handler.hpp"

class Entity
{
  public:
    Entity(ParticleHandler &particles, Entity *parent = nullptr)
        : r_particleHandler(particles), m_interactionBox(particles)
    {
        m_parent = parent;
    }
    virtual ~Entity() = default;

    virtual void update(float dt,
                        const std::vector<const Entity *> &nearbyEntities) = 0;
    virtual void render(Viewport &viewport, const Camera &camera) = 0;

    const Entity *const getParent() const { return m_parent; }
    const EntityKineticBody &getBody() const { return m_body; }
    EntityMetadata getMetadata() const { return m_metadata; }

    void kill() { m_dead = true; }
    void damage(float amount) { m_health -= amount; }
    bool isDead() const { return m_dead; }

  protected:
    virtual void updateMotion(float dt);
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
    void applyExternalMotion();

    Vec2<int> updateMotion_step(Vec2<int> currentPos, Vec2<float> velocity);
    void updateMotion_moveAndPreventWorldCollision(Vec2<int> currentPos,
                                                   float dt);

  protected:
    ParticleHandler &r_particleHandler;
    EntityInteractionBox m_interactionBox;
    EntityKineticBody m_body;

    EntityMetadata m_metadata;

  private:
    Entity *m_parent = nullptr;

    float m_health = 100.0f;
    bool m_dead = false;
};
