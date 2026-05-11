#pragma once

#include "ai/state_machine/state_machine.hpp"
#include "entities/wuskkogel/ai/states.hpp"

class WuskkogelStateMachine : public StateMachine<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelStateMachine() { switch_state(WuskkogelStateID::Roam); }

  protected:
    void switch_state(WuskkogelStateID state) override;
};
