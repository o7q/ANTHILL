#include "player_projectile.hpp"

#include "events/entity/events.hpp"
#include "events/external/events.hpp"
#include "events/particle/events.hpp"
#include "px/utils/line.hpp"
#include "px/utils/random.hpp"
#include "world/particle_handler/particle.hpp"
#include <memory>

void PlayerProjectile::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_body.setVelocity(m_constantVelocity);

    px::Vec2i start = m_body.getPosition();
    m_body.update(context.time.dt);
    px::Vec2i end = m_body.getPosition();

    px::Utils::Lines::bresenhamLine(
        {start, end},
        [&](px::Vec2i pos)
        {
            const Particle *p = context.particleHandler.getParticles().get(pos);
            if (p && p->isSolid())
            {
                auto setEvent      = std::make_unique<ParticleSetRadiusEvent>();
                setEvent->position = pos;
                setEvent->radius   = px::Utils::Random::unseededRandomInt(3, 6);
                setEvent->particle = Particle{};
                eventsOut.emit(std::make_unique<EntityParticleEvent>(context.id, std::move(setEvent)));

                auto forceEvent      = std::make_unique<ParticleApplyForceEvent>();
                forceEvent->position = pos;
                forceEvent->radius   = 8;
                forceEvent->power    = 2;
                eventsOut.emit(std::make_unique<EntityParticleEvent>(context.id, std::move(forceEvent)));

                auto soundEvent             = std::make_unique<ExternalPlaySoundEvent>();
                soundEvent->soundID         = SoundID::SumiHitmarker1;
                soundEvent->settings.volume = 0.6f;
                eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(soundEvent)));

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
                    soundEvent->soundID         = SoundID::SumiHitmarker1;
                    soundEvent->settings.volume = 0.6f;
                    eventsOut.emit(std::make_unique<EntityExternalEvent>(context.id, std::move(soundEvent)));

                    kill();
                    return true;
                }
            }

            return false;
        });
}
