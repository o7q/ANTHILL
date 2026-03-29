#pragma once

#include "events/particle/base.hpp"

struct EntityParticleDrawEvent
{
    EntityParticleDrawEvent(const uint64_t caller) : caller(caller) {}

    ParticleDrawEvent particleEvent;
    const uint64_t caller;
};
