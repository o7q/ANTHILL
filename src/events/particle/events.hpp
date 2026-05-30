#pragma once

#include "base.hpp"
#include "world/particle_handler/particle.hpp"

struct ParticleSetRadiusEvent : public ParticleEvent
{
    ParticleSetRadiusEvent() : ParticleEvent(ParticleEventType::SetRadius) {}
    virtual ~ParticleSetRadiusEvent() = default;

    Particle particle;
    unsigned int radius = 5;
};

struct ParticleApplyForceEvent : public ParticleEvent
{
    ParticleApplyForceEvent() : ParticleEvent(ParticleEventType::ApplyForce) {}
    virtual ~ParticleApplyForceEvent() = default;

    int radius = 0;
    int power  = 0;
};
