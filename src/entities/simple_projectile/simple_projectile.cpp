#include "simple_projectile.hpp"
#include "events/entity/entity_entity.hpp"
#include "events/entity/entity_particle.hpp"
#include "math/line.hpp"
#include "math/random.hpp"
#include "world/particle_world/particle.hpp"
#include <memory>

void SimpleProjectile::update(const EntityWorldContext &worldContext,
                              EventPool<EntityEvent> &eventsOut)
{
    m_body.setVelocity(m_constantVelocity);

    Vec2i start = m_body.getPosition();
    m_body.update(worldContext.dt);
    Vec2i end = m_body.getPosition();

    Math::Line::bresenhamLine(
        start, end,
        [&](Vec2i pos)
        {
            const Particle *p = worldContext.world.getParticles().get(pos);
            if (p && p->isSolid())
            {
                auto event =
                    std::make_unique<EntityParticleDrawEvent>(worldContext.id);
                event->particleEvent.position = pos;
                event->particleEvent.radius = Math::Random::weakRandInt(3, 6);
                event->particleEvent.particle = Particle();

                eventsOut.emit(std::move(event));

                kill();
                return true;
            }

            for (auto &[id, entity] : worldContext.nearbyEntities)
            {
                if (entity->pointInside(pos) &&
                    entity->getMetadata().type != m_metadata.type &&
                    id != getParent())
                {
                    auto event =
                        std::make_unique<EntityDamageEvent>(worldContext.id);
                    event->damage = 5;
                    event->target = id;
                    eventsOut.emit(std::move(event));

                    auto event2 = std::make_unique<EntityParticleDrawEvent>(
                        worldContext.id);
                    Particle blood;
                    blood.setMatterType(Particle::MatterType::Liquid);
                    blood.setPhysicsType(Particle::PhysicsType::Water);
                    blood.setColor(Color(176, 7, 24, 220));

                    Vec2f dir = (m_body.getPositionFloat() -
                                 m_body.getLastPositionFloat())
                                    .normalize() *
                                1.0f;

                    blood.getVerlet().addForce(dir);
                    event2->particleEvent.particle = blood;
                    event2->particleEvent.radius = 3;
                    event2->particleEvent.position = pos;
                    eventsOut.emit(std::move(event2));

                    kill();
                    return true;
                }
            }

            return false;
        });
}
