#pragma once

#include "ai/state_machine/state.hpp"
#include "px/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"

class WuskkogelRoamState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelRoamState() : State(WuskkogelStateID::Roam)
    {
        m_roamMoveTimer.setDurationInSeconds(0.5f);
        m_roamMoveTimer.setMode(Timer::Mode::Repeat);
        m_roamMoveTimer.restart();
    }

    WuskkogelStateID update(const UpdateContext &context);

  private:
    Vec2i m_randomMoveDirection;
    Timer m_roamMoveTimer;
};
