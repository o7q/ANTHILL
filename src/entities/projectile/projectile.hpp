#pragma once

#include "backend/viewport/viewport.hpp"
#include "entity/entity.hpp"
#include "entity/events.hpp"
#include "entity/interfaces/directional.hpp"
#include <memory>

class Projectile : public Entity, public IDirectional
{
  public:
    Projectile(uint64_t id, Vec2<int> pos, float angle) : Entity(id)
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
            auto event = std::make_unique<EntityWorldModifyDrawEvent>(this);

            event->pos = m_body.getPosition();
            event->radius = 30;
            event->particle = Particle();

            m_eventEmitter.emit(std::move(event));

            kill();
        }

        for (auto &e : context.nearbyEntities)
        {
            if (e == this)
            {
                continue;
            }

            if (e->getInteractionBox().pointInside(e->getBody().getPosition(),
                                                   m_body.getPosition().x,
                                                   m_body.getPosition().y))
            {
                // auto event = std::make_unique<EntityDamageEvent>(this);

                // event->damage = 25;
                // // event->target = e;

                // m_eventEmitter.emit(std::move(event));
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
