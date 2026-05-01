#pragma once

#include "ai/state_machine/state.hpp"
#include <memory>

template <typename StateID, typename Context> class StateMachine
{
  public:
    void update(const Context &context)
    {
        if (!m_currentState)
        {
            return;
        }

        StateID state = m_currentState->update(context);

        if (state != m_currentState->getSelfID())
        {
            switch_state(state);
        }
    }

  protected:
    virtual void switch_state(StateID state) = 0;

    void set_current_state(std::unique_ptr<State<StateID, Context>> state)
    {
        m_currentState = std::move(state);
    }

    State<StateID, Context> *get_current_state() { return m_currentState.get(); }

  private:
    std::unique_ptr<State<StateID, Context>> m_currentState = nullptr;
};
