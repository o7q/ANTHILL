#include "player.hpp"

#include "entity/world_interaction/against.hpp"

void Player::update_movement(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    float velX = 0.0f;
    if (r_input.getInput(InputID::Left)->isDown())
    {
        velX -= 3.0f;
    }
    if (r_input.getInput(InputID::Right)->isDown())
    {
        velX += 3.0f;
    }
    m_body.setVelocityTargetX(velX);
    if (r_input.getInput(InputID::Jump)->wasPressed())
    {
        m_jumpHandler.requestJump();
    }
    if (!r_input.getInput(InputID::Jump)->isDown())
    {
        m_jumpHandler.cancelJump();
    }

    bool onGround = EntityWorldInteraction::againstSolidSurface(
        m_body.getPosition(), m_boundingBox, context.particleHandler, RectangleSide::Bottom);

    m_jumpHandler.update(m_body, context.time.dt, onGround);

    if (r_input.getInput(InputID::Dash)->isDown())
    {
        m_dashHandler.start(m_angle);
    }
    else
    {
        m_dashHandler.stop();
    }

    m_dashHandler.update(m_body, eventsOut, context);

    m_bodyHandler.update(context);
}
