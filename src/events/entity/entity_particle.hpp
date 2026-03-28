#pragma once

#include "events/entity/base.hpp"
#include "events/particle/base.hpp"

struct EntityParticleDrawEvent : public EntityEvent
{
    EntityParticleDrawEvent(const uint64_t caller)
        : EntityEvent(caller, EntityEventType::ParticleDraw)
    {
    }

    ParticleDrawEvent particleEvent;
};
