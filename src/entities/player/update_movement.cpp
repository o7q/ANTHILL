#include "player.hpp"

#include "entity/world_interaction/against.hpp"

void Player::update_movement_and_jump(const EntityUpdateContext &context)
{
    float velocityX = 0.0f;
    if (r_input.getInput("left").isDown())
    {
        velocityX -= 3.0f;
    }
    if (r_input.getInput("right").isDown())
    {
        velocityX += 3.0f;
    }
    m_body.setVelocityTargetX(velocityX);

    if (r_input.getInput("jump").wasPressed())
    {
        m_jumpHandler.requestJump();
    }
    if (!r_input.getInput("jump").isDown())
    {
        m_jumpHandler.cancelJump();
    }

    bool onGround = EntityWorldInteraction::againstSolidSurface(
        m_body.getPosition(), m_collider, context.particleHandler, px::RectangleSide::Bottom);

    m_jumpHandler.update(context.time.getDeltaTime(), onGround);

    if (m_jumpHandler.canApplyJumpPower())
    {
        m_body.setVelocityY(-m_jumpHandler.getJumpPower());
    }
}
