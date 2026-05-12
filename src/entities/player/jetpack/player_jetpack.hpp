#pragma once

#include "core/timer/timer.hpp"
#include "entity/body/entity_body.hpp"
class PlayerJetpack
{
  private:
    enum class State
    {
        Idle,
        Active,
        Drained
    };

  public:
    void start();
    void stop();
    void update(EntityBody &body, float dt);

  private:
    State m_state = State::Idle;

    Timer m_fuelTimer;
};
