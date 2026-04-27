#include "entity/world_interaction/against.hpp"
#include "player.hpp"

void Player::update_movement(const EntityUpdateContext &context,
                             EventPool<EntityEvent> &eventsOut)
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
        m_body.getPosition(), m_boundingBox, context.particleHandler,
        RectangleSide::Bottom);

    m_jumpHandler.update(context.dt, onGround);

    if (m_jumpHandler.canJump())
    {
        m_body.setVelocityY(-m_jumpHandler.getJumpPower());
    }

    m_bodyHandler.update(context);
}
