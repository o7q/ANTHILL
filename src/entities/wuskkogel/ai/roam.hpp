#pragma once

#include "ai/state_machine/state.hpp"
#include "entities/wuskkogel/ai/states.hpp"
#include "px/timer/timer.hpp"

class WuskkogelRoamState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelRoamState() : State(WuskkogelStateID::Roam)
    {
        m_roamMoveTimer.setDurationInSeconds(0.5f);
        m_roamMoveTimer.setMode(px::Timer::Mode::Repeat);
        m_roamMoveTimer.restart();
    }

    WuskkogelStateID update(const UpdateContext &context);

  private:
    px::Vec2i m_randomMoveDirection;
    px::Timer m_roamMoveTimer;
};
