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

        m_currentStateID = m_currentState->update(context);

        if (m_currentStateID != m_currentState->getSelfID())
        {
            switch_state(m_currentStateID);
        }
    }

    StateID getCurrentStateID() const { return m_currentStateID; }

  protected:
    virtual void switch_state(StateID state) = 0;

    void set_current_state(std::unique_ptr<State<StateID, Context>> state)
    {
        m_currentState = std::move(state);
    }

    State<StateID, Context> *get_current_state() { return m_currentState.get(); }

  private:
    StateID m_currentStateID{};
    std::unique_ptr<State<StateID, Context>> m_currentState = nullptr;
};
