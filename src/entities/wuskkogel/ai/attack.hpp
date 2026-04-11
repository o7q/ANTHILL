#pragma once

#include "ai/state_machine/state.hpp"
#include "backend/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"

class WuskkogelAttackState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelAttackState(uint64_t &targetID)
        : State(WuskkogelStateID::Attack), r_targetID(targetID)
    {
        m_attackTimer.setDurationInSeconds(0.5f);
    }

    WuskkogelStateID update(const UpdateContext &context);

  private:
    uint64_t &r_targetID;

    bool m_bit = false;

    Timer m_attackTimer;
};
