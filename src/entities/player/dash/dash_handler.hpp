#pragma once

#include "backend/timer/timer.hpp"
#include "entity/body/entity_body.hpp"
#include "entity/update_context.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"

class DashHandler
{
  public:
    enum class State
    {
        Idle,
        Charging,
        Dashing,
        Drained
    };

  public:
    DashHandler();

    void start(float angle);
    void stop();

    void update(EntityBody &body, EventPool<EntityEvent> &eventsOut, const EntityUpdateContext &context);

  private:
    State m_state = State::Idle;

    Timer m_startTimer;
    Timer m_dashTimer;

    float m_dashAngle;
};
