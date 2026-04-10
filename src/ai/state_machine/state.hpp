#pragma once

template <typename StateID, typename Context> class State
{
  public:
    State(StateID selfID) : m_selfID(selfID) {}

    virtual StateID update(const Context &context) = 0;

    StateID getSelfID() const { return m_selfID; }

  private:
    const StateID m_selfID;
};
