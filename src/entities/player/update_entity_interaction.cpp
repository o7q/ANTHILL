#include "core/math/distance.hpp"
#include "core/math/line.hpp"
#include "player.hpp"

void Player::update_entity_interaction(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_dashTarget          = std::nullopt;
    float closestDistance = std::numeric_limits<float>::max();
    for (auto &entity : context.otherEntities)
    {
        float dist =
            Math::Distance::euclidian(entity.second->getBody().getPositionFloat(), m_aimPos.toFloat());
        if (dist < closestDistance && dist < 30.0f &&
            entity.second->getMetadata().type != EntityType::Projectile &&
            entity.second->getMetadata().type != EntityType::Collectible)
        {
            GridRectangle rect(entity.second->getBody().getPosition(),
                               entity.second->getCollider().getPrimary().getSize());

            m_dashTarget    = rect;
            closestDistance = dist;
        }

        if (m_dash.getState() == PlayerDash::State::Dashing)
        {
            Math::Line::bresenhamLine(m_body.getPosition(), m_body.getLastPosition(),
                                      [&](Vec2i p)
                                      {
                                          if (entity.second->getCollider().overlappingAny(
                                                  entity.second->getBody().getPosition(), p, m_collider))
                                          {
                                              auto entityDamageEvent =
                                                  std::make_unique<EntityDamageEvent>(context.id);
                                              entityDamageEvent->target           = entity.first;
                                              entityDamageEvent->source.amount    = 20;
                                              entityDamageEvent->source.position  = p;
                                              entityDamageEvent->source.direction = m_body.getVelocity();

                                              eventsOut.emit(std::move(entityDamageEvent));
                                          }

                                          return false;
                                      });
        }
    }
}
