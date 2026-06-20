#pragma once

#include "ai/state_machine/state.hpp"
#include "px/timer/timer.hpp"
#include "entities/wuskkogel/ai/states.hpp"

class WuskkogelAttackState : public State<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelAttackState() : State(WuskkogelStateID::Attack) { m_attackTimer.setDurationInSeconds(0.5f); }

    WuskkogelStateID update(const UpdateContext &context);

  private:
    bool m_attacked = false;

    px::Timer m_attackTimer;
};
