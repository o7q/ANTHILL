#pragma once

#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/entity/entity_particle.hpp"
#include "events/event_emitter.hpp"
#include <iostream>
#include <memory>

class Projectile : public Entity
{
  public:
    Projectile(uint64_t id, uint64_t parent, Vec2i pos, float angle)
        : Entity(id, parent)
    {
        m_body.setPosition(pos);

        m_interactionBox.getBoundingBox().setSize({3, 3});

        m_direction = {std::cosf(angle), std::sinf(angle)};

        m_metadata.name = "Projectile";
    }

    virtual void update(const EntityUpdateContext &context) override
    {
        m_body.setVelocity(m_direction * 5.0f);

        const Particle *p =
            context.world.getParticles().get(m_body.getPosition());

        if (p && p->isSolid())
        {
            auto event = std::make_unique<EntityParticleDrawEvent>(getID());
            event->particleEvent.position = m_body.getPosition();
            event->particleEvent.radius = 30;
            event->particleEvent.particle = Particle();

            m_eventEmitter.emit(std::move(event));

            kill();
        }

        for (const Entity *e : context.nearbyEntities)
        {
            if (e->getID() == getID() || e->getID() == getParent())
            {
                continue;
            }

            if (e->getInteractionBox().pointInside(e->getBody().getPosition(),
                                                   m_body.getPosition()))
            {
                auto event = std::make_unique<EntityDamageEvent>(getID());
                event->target = e->getID();
                event->damage = 5;

                m_eventEmitter.emit(std::move(event));

                kill();
            }
        }

        m_body.update(context.dt);
    }
    void render(Viewport &viewport, const Camera &camera) override
    {
        DEBUG_renderBoundingBox(viewport, camera);
    }

  private:
    Vec2f m_direction;
};
