#pragma once

#include "ai/state_machine/state.hpp"
#include "core/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"

class WuskkogelFollowState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelFollowState(uint64_t &targetID) : State(WuskkogelStateID::Follow), r_targetID(targetID)
    {
        m_targetLostTimer.setDurationInSeconds(5.0f);
        m_targetLostTimer.restart();
    }

    WuskkogelStateID update(const UpdateContext &context);

  private:
    uint64_t &r_targetID;

    Timer m_targetLostTimer;
};
