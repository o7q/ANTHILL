#include "player_projectile.hpp"

#include "core/math/line.hpp"
#include "core/math/random.hpp"
#include "events/entity/events.hpp"
#include "events/external/events.hpp"
#include "events/particle/events.hpp"
#include "world/particle_handler/particle.hpp"
#include <memory>

void PlayerProjectile::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
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

            for (auto &[id, entity] : context.otherEntities)
            {
                if (entity->getCollider().pointInsideAny(entity->getBody().getPosition(), pos) &&
                    entity->getMetadata().type != m_metadata.type && id != getParent())
                {
                    auto event             = std::make_unique<EntityDamageEvent>(context.id);
                    event->target          = id;
                    event->source.amount   = 10;
                    event->source.position = m_body.getPosition();
                    event->source.direction =
                        (m_body.getPositionFloat() - m_body.getLastPositionFloat()).normalize() * 1.0f;
                    eventsOut.emit(std::move(event));

                    auto soundEvent             = std::make_unique<ExternalPlaySoundEvent>();
                    soundEvent->soundID         = SoundID::SumiGunHit1;
                    soundEvent->settings.volume = 0.3f;
                    eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(soundEvent)));

                    kill();
                    return true;
                }
            }

            return false;
        });
}
