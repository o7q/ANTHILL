#pragma once

#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/interfaces/directional.hpp"
#include "event/event_emitter.hpp"
#include "world/entity/events/entity.hpp"
#include "world/entity/events/particle.hpp"
#include <iostream>
#include <memory>

class Projectile : public Entity, public IDirectional
{
  public:
    Projectile(uint64_t id, Vec2i pos, float angle) : Entity(id)
    {
        m_body.setPosition(pos.x, pos.y);
        m_lookAngle = angle;
        m_body.setVelocity(std::cosf(angle) * 10, std::sinf(angle) * 10);
        m_interactionBox.getBoundingBox().setSize(3, 3);
        m_body.setGravity(0.1f);
    }

    void update(const EntityUpdateContext &context) override
    {
        const Particle *p = context.particles.getParticles().get(
            m_body.getPosition().x, m_body.getPosition().y);

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
                std::cout << e->getMetadata().name << std::endl;

                auto event = std::make_unique<EntityDamageEvent>(getID());
                event->target = e->getID();
                event->damage = 5;

                auto event2 =
                    std::make_unique<EntityParticleDrawEvent>(getID());
                Particle p;
                p.setMatterType(Particle::MatterType::Liquid);
                p.setPhysicsType(Particle::PhysicsType::Water);
                p.setColor(Color(220, 10, 10));
                p.setRestitution(0.1f);
                event2->particleEvent.particle = p;
                event2->particleEvent.position = e->getBody().getPosition();
                event2->particleEvent.radius = 10;

                m_eventEmitter.emit(std::move(event));
                m_eventEmitter.emit(std::move(event2));

                kill();
            }
        }

        m_body.applyGravity();
        m_body.update(context.dt);
    }
    void render(Viewport &viewport, const Camera &camera) override
    {
        renderDebug_boundingBox(viewport, camera);
    }
};
