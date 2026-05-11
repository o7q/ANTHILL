#pragma once

#include "ai/state_machine/state.hpp"
#include "core/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"

class WuskkogelFollowState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelFollowState() : State(WuskkogelStateID::Follow)
    {
        m_targetLostTimer.setDurationInSeconds(5.0f);
        m_targetLostTimer.restart();
    }

    WuskkogelStateID update(const UpdateContext &context);

  private:
    Timer m_targetLostTimer;
};
