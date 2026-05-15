#include "player.hpp"

#include "core/math/rectangle.hpp"
#include "entities/player/dash/player_dash.hpp"
#include "entity/world_interaction/against.hpp"

void Player::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    update_entity_interaction(context, eventsOut);

    if (r_input.getInput(InputID::Dash)->wasPressed())
    {
        if (m_dashTarget.has_value())
        {
            Vec2i pos = m_dashTarget.value().getPosition();
            m_dash.start(Math::Angles::vectorsToAngle(m_body.getPositionFloat(), pos.toFloat()));
        }
        else
        {
            m_dash.start(Math::Angles::vectorsToAngle(m_body.getPositionFloat(), m_aimPos.toFloat()));
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

    if (r_input.getInput(InputID::Shoot)->isDown())
    {
        m_gun.shoot(m_body.getPosition(), m_angle, context.id, eventsOut);
    }
    m_gun.update(context.time.dt);

    m_bodyHandler.update(context);

    m_sprite.update({m_body, m_dash, m_angle}, context.time.dt);
    m_sound.update(
        context,
        {m_body, EntityWorldInteraction::againstSolidSurface(m_body.getPosition(), m_collider,
                                                             context.particleHandler, RectangleSide::Bottom)},
        eventsOut);
}
