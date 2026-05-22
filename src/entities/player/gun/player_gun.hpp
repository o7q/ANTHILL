#pragma once

#include "core/math/angle.hpp"
#include "core/math/geometry/vec.hpp"
#include "core/timer/timer.hpp"
#include "events/entity/base.hpp"
#include "events/event_pool.hpp"

class PlayerGun
{
  public:
    PlayerGun();

    void update(float dt);
    void shoot(Vec2i pos, Angle aimPos, uint64_t id, EventPool<EntityEvent> &eventsOut);

  private:
    Timer m_shootCooldown;
};
