#pragma once

#include "ai/state_machine/state.hpp"
#include "backend/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"

class WuskkogelRoamState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelRoamState(uint64_t &targetID) : State(WuskkogelStateID::Roam), r_targetID(targetID)
    {
        m_roamMoveTimer.setDurationInSeconds(1.0f);
        m_roamMoveTimer.setMode(Timer::Mode::Repeat);
        m_roamMoveTimer.restart();
    }

    WuskkogelStateID update(const UpdateContext &context);

  private:
    uint64_t &r_targetID;

    Vec2i moveDir;
    Timer m_roamMoveTimer;
};
