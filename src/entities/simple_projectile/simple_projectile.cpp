#include "simple_projectile.hpp"
#include "entity/world_interaction/trajectory.hpp"
#include "events/entity/entity_particle.hpp"
#include "math/random.hpp"

void SimpleProjectile::update(const EntityUpdateContext &context,
                              EventPool<EntityEvent> &eventsOut)
{
    m_body.setVelocity(m_constantVelocity);

    Vec2i start = m_body.getPosition();
    m_body.update(context.dt);
    Vec2i end = m_body.getPosition();

    EntityWorldInteraction::TrajectoryCollisionResponse response =
        EntityWorldInteraction::calculateCollisionFromTrajectory(
            start, end, m_boundingBox, context.world);

    if (response.collided)
    {
        auto event = std::make_unique<EntityParticleDrawEvent>(context.id);
        event->particleEvent.position = response.hitPosition;
        event->particleEvent.radius = Math::Random::weakRandInt(3, 6);
        event->particleEvent.particle = Particle();

        eventsOut.emit(std::move(event));

        kill();
    }
}
