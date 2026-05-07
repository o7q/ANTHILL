#include "player.hpp"

#include "entities/player/dash/dash_handler.hpp"
#include "events/entity/events.hpp"
#include "math/distance.hpp"
#include "math/line.hpp"
#include "math/rectangle.hpp"
#include <memory>

void Player::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_highlightRects.clear();
    for (auto &entity : context.nearbyEntities)
    {
        if (Math::Distance::euclidian(entity.second->getBody().getPositionFloat(), m_aimPos.toFloat()) <
            50.0f)
        {
            PositionalGridRectangle rect;
            rect.setSize(entity.second->getBoundingBox().getSize());
            rect.setPosition(entity.second->getBody().getPosition());
            m_highlightRects.push_back(rect);
        }

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

    if (r_input.getInput(InputID::Dash)->isDown())
    {
        if (m_highlightRects.size() > 0)
        {
            Vec2i pos     = m_highlightRects[0].getPosition();
            float degrees = Math::Angles::vectorsToAngle(m_body.getPositionFloat(), pos.toFloat()).degrees();
            m_dashHandler.start(degrees);
        }
    }

    m_dashHandler.update(context);

    if (m_dashHandler.getState() == DashHandler::State::Dashing)
    {
        m_body.setVelocity(m_dashHandler.getDashVelocity());
    }
    else
    {
        update_movement_and_jump(context, eventsOut);
        update_items(context, eventsOut);
    }

    m_bodyHandler.update(context);
    m_sprite.update({m_body, m_angle, m_dashHandler.getState() == DashHandler::State::Dashing, false},
                    context.time.dt);
}
