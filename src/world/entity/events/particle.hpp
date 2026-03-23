#pragma once

#include "event.hpp"
#include "world/particle/events/event.hpp"

struct EntityParticleDrawEvent : public EntityEvent
{
    EntityParticleDrawEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::ParticleDraw)
    {
    }

    ParticleDrawEvent particleEvent;
};
