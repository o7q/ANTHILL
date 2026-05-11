#include "player.hpp"

#include "core/math/distance.hpp"
#include "core/math/line.hpp"
#include "core/math/rectangle.hpp"
#include "entities/player/dash/player_dash.hpp"
#include "entity/world_interaction/against.hpp"
#include "events/entity/events.hpp"
#include <limits>
#include <memory>

void Player::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    m_dashTarget          = std::nullopt;
    float closestDistance = std::numeric_limits<float>::max();
    for (auto &entity : context.otherEntities)
    {
        float dist =
            Math::Distance::euclidian(entity.second->getBody().getPositionFloat(), m_aimPos.toFloat());
        if (dist < closestDistance && dist < 150.0f)
        {
            PositionalGridRectangle rect;
            rect.setSize(entity.second->getBoundingBox().getSize());
            rect.setPosition(entity.second->getBody().getPosition());

            m_dashTarget    = rect;
            closestDistance = dist;
        }

        if (m_dash.getState() == PlayerDash::State::Dashing)
        {
            Math::Line::bresenhamLine(m_body.getPosition(), m_body.getLastPosition(),
                                      [&](Vec2i p)
                                      {
                                          if (entity.second->pointInside(p))
                                          {
                                              auto entityDamageEvent =
                                                  std::make_unique<EntityDamageEvent>(context.id);
                                              entityDamageEvent->target           = entity.first;
                                              entityDamageEvent->source.amount    = 20;
                                              entityDamageEvent->source.position  = m_body.getPosition();
                                              entityDamageEvent->source.direction = m_body.getVelocity();

                                              eventsOut.emit(std::move(entityDamageEvent));

                                              auto slowmoEvent = std::make_unique<ExternalChangeSpeedEvent>();
                                              slowmoEvent->settings.startLength = 0;
                                              slowmoEvent->settings.holdLength  = 0.5f;
                                              slowmoEvent->settings.holdSpeed   = 0.2f;
                                              slowmoEvent->settings.endLength   = 1.0f;

                                              eventsOut.emit(std::make_unique<EntityExternalEvent>(
                                                  context.id, std::move(slowmoEvent)));
                                          }

                                          return false;
                                      });
        }
    }

    if (r_input.getInput(InputID::Dash)->wasPressed())
    {
        if (m_dashTarget.has_value())
        {
            Vec2i pos = m_dashTarget.value().getPosition();
            m_dash.start(Math::Angles::vectorsToAngle(m_body.getPositionFloat(), pos.toFloat()));
        }
    }

    if (r_input.getInput(InputID::Dash)->wasUnpressed())
    {
        m_dash.stop();
    }

    m_dash.update(context);

    if (m_dash.getState() == PlayerDash::State::Dashing)
    {
        m_body.setVelocity(m_dash.getDashVelocity());
    }
    else
    {
        update_movement_and_jump(context);
    }

    m_bodyHandler.update(context);
    m_sprite.update({m_body, m_dash, m_angle}, context.time.dt);

    m_sound.update(
        context,
        {m_body, EntityWorldInteraction::againstSolidSurface(m_body.getPosition(), m_boundingBox,
                                                             context.particleHandler, RectangleSide::Bottom)},
        eventsOut);
}
