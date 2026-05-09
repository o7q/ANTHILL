#pragma once

#include "core/math/angle.hpp"
#include "core/timer/timer.hpp"
#include "entity/update_context.hpp"

class PlayerDash
{
  public:
    enum class State
    {
        Idle,
        Charging,
        Dashing
    };

  public:
    PlayerDash();

    void start(Angle angle);
    void stop();

    void update(const EntityUpdateContext &context);

    State getState() const { return m_state; }
    Vec2f getDashVelocity() const { return m_dashVelocity; }

  private:
    void dash_update_velocity();

  private:
    State m_state = State::Idle;
    Vec2f m_dashVelocity;

    Timer m_startTimer;
    Timer m_dashTimer;

    float m_dashAngle;
};
