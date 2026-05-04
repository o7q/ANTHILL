#include "entities/player/dash/dash_handler.hpp"
#include "events/entity/events.hpp"
#include "events/particle/events.hpp"
#include "math/line.hpp"
#include "player.hpp"
#include <iostream>
#include <memory>

void Player::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    update_movement(context, eventsOut);
    update_items(context, eventsOut);

    for (auto &entity : context.nearbyEntities)
    {
        if (m_dashHandler.getState() == DashHandler::State::Dashing)
        {
            Math::Line::bresenhamLine(m_body.getPosition(), m_body.getLastPosition(),
                                      [&](Vec2i p)
                                      {
                                          if (entity.second->pointInside(p))
                                          {
                                              auto test    = std::make_unique<EntityDamageEvent>(context.id);
                                              test->target = entity.first;
                                              test->source.amount    = 20;
                                              test->source.position  = m_body.getPosition();
                                              test->source.direction = m_body.getVelocity();

                                              eventsOut.emit(std::move(test));
                                          }

                                          return false;
                                      });
        }
    }

    m_bodyHandler.update(context);
    m_sprite.update({m_body, m_angle, false, false, false}, context.time.dt);
}
