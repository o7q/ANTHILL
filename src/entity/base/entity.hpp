#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "entities/metadata.hpp"
#include "entity/base/kinetic_body/entity_kinetic_body.hpp"
#include "interaction/entity_interaction_box.hpp"
#include "utils/render.hpp"
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

    virtual void update(float dt) { updateInternal(dt); }
    virtual void render(Viewport &viewport, const Camera &camera)
    {
        Vec2<int> pos = m_body.getPosition().toGrid();

        Vec2<int> a = m_interactionBox.getBoundingBox().getA() + pos;
        Vec2<int> b = m_interactionBox.getBoundingBox().getB() + pos;

        a = camera.worldToViewport(a.x, a.y);
        b = camera.worldToViewport(b.x, b.y);

        Utils::Render::drawRectOutline(viewport, a, b, Color(245, 66, 120));
    }

    EntityKineticBody &getBody() { return m_body; }

    void kill() { m_dead = true; }
    bool isDead() const { return m_dead; }

    Entity *getParent() { return m_parent; }

    EntityMetadata getMetadata() const { return m_metadata; }

  protected:
    virtual void updateInternal(float dt) { updateMotion(dt); }
    virtual void updateMotion(float dt);

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

    bool m_dead = false;
};
