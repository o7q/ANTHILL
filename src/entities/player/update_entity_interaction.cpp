#include "player.hpp"

#include "events/entity/events.hpp"
#include "events/external/events.hpp"
#include "px/utils/line.hpp"

void Player::update_entity_interaction(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    for (auto &e : context.otherEntities)
    {
        uint64_t id             = e.first;
        const Entity *entity    = e.second;
        EntityMetadata metadata = entity->getMetadata();

        px::Utils::Lines::bresenhamLine(
            {m_body.getLastPosition(), m_body.getPosition()},
            [&](px::Vec2i p)
            {
                if (m_collider.overlappingAny(p, entity->getBody().getPosition(), entity->getCollider()))
                {
                    if (m_dash.getState() == PlayerDash::State::Dashing)
                    {
                        auto entityDamageEvent              = std::make_unique<EntityDamageEvent>(context.id);
                        entityDamageEvent->target           = id;
                        entityDamageEvent->source.amount    = 50;
                        entityDamageEvent->source.position  = p;
                        entityDamageEvent->source.direction = m_body.getVelocity();
                        if (entity->getHealth() <= 50)
                        {
                            auto entityKillSoundEvent     = std::make_unique<ExternalPlaySoundEvent>();
                            entityKillSoundEvent->soundID = SoundID::SumiDashKill1;
                            entityKillSoundEvent->settings.volume = 0.2f;
                            entityKillSoundEvent->settings.pitch =
                                px::Utils::Random::unseededRandomInt(90, 100) / 100.0f;
                            eventsOut.emit(std::make_unique<EntityExternalEvent>(
                                context.id, std::move(entityKillSoundEvent)));
                        }

                        eventsOut.emit(std::move(entityDamageEvent));
                        return true;
                    }

                    if (entity->getMetadata().type == EntityType::Energy)
                    {
                        auto entityKillEvent    = std::make_unique<EntityKillEvent>(context.id);
                        entityKillEvent->target = id;

                        eventsOut.emit(std::move(entityKillEvent));

                        m_energy++;
                        return true;
                    }
                }

                return false;
            });
    }
}
