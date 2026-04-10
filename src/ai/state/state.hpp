#pragma once

#include "entity/update_context.hpp"
#include "events/entity/base.hpp"

template <typename StateID> class State
{
  public:
    State(StateID selfID) : m_selfID(selfID) {}

    virtual StateID update(const EntityUpdateContext &context,
                           EventPool<EntityEvent> &eventsOut) = 0;

    StateID getSelfID() const { return m_selfID; }

  private:
    const StateID m_selfID;
};
