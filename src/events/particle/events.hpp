#pragma once

#include "base.hpp"
#include "world/particle_handler/particle.hpp"

struct ParticleDrawEvent : public ParticleEvent
{
    ParticleDrawEvent() : ParticleEvent(ParticleEventType::SetRadius) {}
    virtual ~ParticleDrawEvent() = default;

    Particle particle;
    unsigned int radius = 5;
};
