#pragma once

#include "events/entity/base.hpp"
#include "events/particle/base.hpp"

struct EntityParticleDrawEvent : public EntityEvent
{
    EntityParticleDrawEvent(const uint64_t caller_)
        : EntityEvent(caller_, EntityEventType::ParticleDraw)
    {
    }

    ParticleDrawEvent particleEvent;
};
