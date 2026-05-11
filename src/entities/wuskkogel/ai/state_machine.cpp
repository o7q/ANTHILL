#include "state_machine.hpp"

#include "entities/wuskkogel/ai/attack.hpp"
#include "entities/wuskkogel/ai/follow.hpp"
#include "entities/wuskkogel/ai/roam.hpp"

void WuskkogelStateMachine::switch_state(WuskkogelStateID state)
{
    switch (state)
    {
    case WuskkogelStateID::Follow:
        set_current_state(std::make_unique<WuskkogelFollowState>());
        break;
    case WuskkogelStateID::Roam:
        set_current_state(std::make_unique<WuskkogelRoamState>());
        break;
    case WuskkogelStateID::Attack:
        set_current_state(std::make_unique<WuskkogelAttackState>());
        break;
    }
}
