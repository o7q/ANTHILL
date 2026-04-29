#include "player_sprite.hpp"

void PlayerSprite::update(UpdateData data, float dt)
{
    State state = determine_state(data.body);

    if (state != m_lastState)
    {
        m_head.restartAll();
        m_torso.restartAll();
        m_legs.restartAll();
    }

    update_head(state, data.lookAngle, dt);
    update_torso(state, dt);
    update_legs(state, dt);

    m_lastState = state;
}

void PlayerSprite::update_head(State state, float lookAngle, float dt)
{
    const bool lookingUp45   = std::abs(lookAngle + 90.0f) < 65.0f;
    const bool lookingDown45 = std::abs(lookAngle - 90.0f) < 65.0f;

    switch (state)
    {
    case State::Idle:
        if (lookingUp45)
        {
            m_head.switchAnimator(HeadAnimation::IdleUp45);
        }
        else if (lookingDown45)
        {
            m_head.switchAnimator(HeadAnimation::IdleDown45);
        }
        else
        {
            m_head.switchAnimator(HeadAnimation::Idle);
        }
        break;
    case State::Run:
        if (lookingUp45)
        {
            m_head.switchAnimator(HeadAnimation::RunUp45);
        }
        else if (lookingDown45)
        {
            m_head.switchAnimator(HeadAnimation::RunDown45);
        }
        else
        {
            m_head.switchAnimator(HeadAnimation::Run);
        }
        break;
    default:
        break;
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
