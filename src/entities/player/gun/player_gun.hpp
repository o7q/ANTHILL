#pragma once

#include "events/entity/base.hpp"
#include "events/event_pool.hpp"
#include "px/basic_types/angle.hpp"
#include "px/basic_types/vec.hpp"
#include "px/timer/timer.hpp"

class PlayerGun
{
  public:
    PlayerGun();

    void update(float dt);
    void shoot(px::Vec2i pos, px::Angle aimPos, uint64_t id, EventPool<EntityEvent> &eventsOut);

  private:
    px::Timer m_shootCooldown;
};
