#pragma once

#include "ai/state_machine/state_machine.hpp"
#include "entities/wuskkogel/ai/attack.hpp"
#include "entities/wuskkogel/ai/follow.hpp"
#include "entities/wuskkogel/ai/roam.hpp"
#include "entities/wuskkogel/ai/states.hpp"
#include <memory>

class WuskkogelStateMachine
    : public StateMachine<WuskkogelStateID, UpdateContext>
{
  public:
    WuskkogelStateMachine() { switch_state(WuskkogelStateID::Roam); }

  protected:
    void switch_state(WuskkogelStateID state) override
    {
        switch (state)
        {
        case WuskkogelStateID::Follow:
            set_current_state(
                std::make_unique<WuskkogelFollowState>(m_targetID));
            break;
        case WuskkogelStateID::Roam:
            set_current_state(std::make_unique<WuskkogelRoamState>(m_targetID));
            break;
        case WuskkogelStateID::Attack:
            set_current_state(
                std::make_unique<WuskkogelAttackState>(m_targetID));
            break;
        }
    }

  private:
    uint64_t m_targetID = 0;
};
