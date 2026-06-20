#include "player.hpp"

#include "entities/player/dash/player_dash.hpp"
#include "entity/world_interaction/against.hpp"
#include "events/entity/base.hpp"

void Player::update(const EntityUpdateContext &context, EventPool<EntityEvent> &eventsOut)
{
    if (r_input.getInput("dash")->wasPressed())
    {
        bool up    = r_input.getInput("up")->isDown();
        bool down  = r_input.getInput("down")->isDown();
        bool left  = r_input.getInput("left")->isDown();
        bool right = r_input.getInput("right")->isDown();

        PlayerDash::Direction direction = PlayerDash::Direction::Left;

        if (up)
        {
            direction = PlayerDash::Direction::Up;
        }
        if (down)
        {
            direction = PlayerDash::Direction::Down;
        }
        if (left)
        {
            direction = PlayerDash::Direction::Left;
        }
        if (right)
        {
            direction = PlayerDash::Direction::Right;
        }
        if (up && left)
        {
            direction = PlayerDash::Direction::UpLeft;
        }
        if (up && right)
        {
            direction = PlayerDash::Direction::UpRight;
        }
        if (down && left)
        {
            direction = PlayerDash::Direction::DownLeft;
        }
        if (down && right)
        {
            direction = PlayerDash::Direction::DownRight;
        }

        m_dash.dash(direction);
    }

    m_dash.update(context);

    if (m_dash.getState() == PlayerDash::State::Dashing)
    {
        m_body.setVelocity(m_dash.getDashVelocity());

        if (r_input.getInput("jump")->wasPressed())
        {
            m_dashJumpRequested = true;
        }
    }
    else
    {
        update_movement_and_jump(context);
    }

    bool onGround = EntityWorldInteraction::againstSolidSurface(
        m_body.getPosition(), m_collider, context.particleHandler, px::RectangleSide::Bottom);

    if (m_dashJumpRequested && onGround)
    {
        m_dash.stop();
        m_body.setVelocityY(-m_body.getVelocity().y * 1.5f);
        m_dashJumpRequested = false;
    }

    if (r_input.getInput("shoot")->isDown())
    {
        m_gun.shoot(m_body.getPosition(), m_angle, context.id, eventsOut);
    }

    m_gun.update(context.time.dt);

    m_bodyHandler.update(context);
}
