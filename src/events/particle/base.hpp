#pragma once

#include "math/vec.hpp"
#include "world/particle_world/particle.hpp"

enum class ParticleEventType
{
    Draw
};

struct ParticleEvent
{
    ParticleEvent(const ParticleEventType type_) : type(type_) {}
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
