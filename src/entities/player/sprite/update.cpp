#include "player_sprite.hpp"

void PlayerSprite::update(const EntityBody &body, float lookAngle, float dt)
{
    State state = determine_state(body);

    if (state != m_lastState)
    {
        m_head.restartAll();
        m_torso.restartAll();
        m_legs.restartAll();
    }

    update_head(state, lookAngle, dt);
    update_torso(state, dt);
    update_legs(state, dt);

    m_lastState = state;
}

void PlayerSprite::update_head(State state, float lookAngle, float dt)
{
    const bool lookingUp45 = std::abs(lookAngle + 90.0f) < 65.0f;
    const bool lookingDown45 = std::abs(lookAngle - 90.0f) < 65.0f;

    if (lookingUp45)
    {
        switch (state)
        {
        case State::Idle:
            m_head.switchAnimator(HeadAnimation::IdleUp45);
            break;
        case State::Run:
        default:
            break;
        }
    }
    else if (lookingDown45)
    {
        switch (state)
        {
        case State::Idle:
            m_head.switchAnimator(HeadAnimation::IdleDown45);
            break;
        case State::Run:
        default:
            break;
        }
    }
    else
    {
        switch (state)
        {
        case State::Idle:
            m_head.switchAnimator(HeadAnimation::Idle);
            break;
        case State::Run:
            m_head.switchAnimator(HeadAnimation::Run);
        default:
            break;
        }
    }

    m_head.update(dt);
}

void PlayerSprite::update_torso(State state, float dt)
{
    switch (state)
    {
    case State::Idle:
        m_torso.switchAnimator(TorsoAnimation::Idle);
        break;
    case State::Run:
        m_torso.switchAnimator(TorsoAnimation::Run);
        break;
    default:
        break;
    }

    m_torso.update(dt);
}

void PlayerSprite::update_legs(State state, float dt)
{
    switch (state)
    {
    case State::Idle:
        m_legs.switchAnimator(LegsAnimation::Idle);
        break;
    case State::Run:
        m_legs.switchAnimator(LegsAnimation::Run);
        break;
    default:
        break;
    }

    m_legs.update(dt);
}
