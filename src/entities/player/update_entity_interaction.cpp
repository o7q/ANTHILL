#include "player.hpp"

#include "core/math/distance.hpp"
#include "core/math/line.hpp"
#include "entity/metadata.hpp"

void Player::update_entity_interaction(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_dashTarget          = std::nullopt;
    float closestDistance = std::numeric_limits<float>::max();
    for (auto &e : context.otherEntities)
    {
        uint64_t id             = e.first;
        const Entity *entity    = e.second;
        EntityMetadata metadata = entity->getMetadata();

        float dist = Math::Distance::euclidian(entity->getBody().getPositionFloat(), m_aimPos.toFloat());
        if (dist < closestDistance && dist < 60.0f && metadata.type != EntityType::Projectile &&
            metadata.type != EntityType::Energy)
        {
            GridRectangle rect(entity->getBody().getPosition(), entity->getCollider().getPrimary().getSize());

            m_dashTarget    = rect;
            closestDistance = dist;
        }

        Math::Line::bresenhamLine(
            m_body.getLastPosition(), m_body.getPosition(),
            [&](Vec2i p)
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

                        m_comboTimer.restart();

                        if (entity->getHealth() <= 50)
                        {
                            m_comboCounter++;
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
