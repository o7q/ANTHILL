#include "simple_projectile.hpp"

#include "events/entity/events.hpp"
#include "events/particle/events.hpp"
#include "math/line.hpp"
#include "math/random.hpp"
#include "world/particle_handler/particle.hpp"
#include <memory>

void SimpleProjectile::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_body.setVelocity(m_constantVelocity);

    Vec2i start = m_body.getPosition();
    m_body.update(context.time.dt);
    Vec2i end = m_body.getPosition();

    Math::Line::bresenhamLine(
        start, end,
        [&](Vec2i pos)
        {
            const Particle *p = context.particleHandler.getParticles().get(pos);
            if (p && p->isSolid())
            {
                auto event      = std::make_unique<ParticleDrawEvent>();
                event->position = pos;
                event->radius   = Math::Random::unseededRandomInt(3, 6);
                event->particle = Particle();

                eventsOut.emit(std::make_unique<EntityParticleEvent>(context.id, std::move(event)));

                kill();
                return true;
            }

            for (auto &[id, entity] : context.nearbyEntities)
            {
                if (entity->pointInside(pos) && entity->getMetadata().type != m_metadata.type &&
                    id != getParent())
                {
                    auto event    = std::make_unique<EntityDamageEvent>(context.id);
                    event->damage = 5;
                    event->target = id;
                    eventsOut.emit(std::move(event));

                    auto event2 = std::make_unique<ParticleDrawEvent>();
                    Particle blood;
                    blood.setMatterType(Particle::MatterType::Liquid);
                    blood.setPhysicsType(Particle::PhysicsType::Water);
                    blood.setColor(Color(255, 0, 0, 220));

                    Vec2f dir =
                        (m_body.getPositionFloat() - m_body.getLastPositionFloat()).normalize() * 1.0f;

                    blood.getVerlet().addForce(dir);
                    event2->particle = blood;
                    event2->radius   = 3;
                    event2->position = pos;
                    eventsOut.emit(std::make_unique<EntityParticleEvent>(context.id, std::move(event2)));

                    kill();
                    return true;
                }
            }

            return false;
        });
}
