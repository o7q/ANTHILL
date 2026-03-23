#pragma once

#include "math/vec.hpp"
#include "world/particle/particle.hpp"
enum class ParticleEventType
{
    Draw
};

struct ParticleEvent
{
    ParticleEvent(const ParticleEventType type) : type(type) {}
    virtual ~ParticleEvent() = default;

    const ParticleEventType type;
    Vec2i position;
};

struct ParticleDrawEvent : public ParticleEvent
{
    ParticleDrawEvent() : ParticleEvent(ParticleEventType::Draw) {}
    virtual ~ParticleDrawEvent() = default;

    Particle particle;
    unsigned int radius = 5;
};
