#pragma once

#include "math/vec.hpp"
#include "world/particle/particle.hpp"
#include <variant>

struct ParticleDrawEvent
{
    ParticleDrawEvent() = default;
    virtual ~ParticleDrawEvent() = default;

    Vec2i position;
    Particle particle;
    unsigned int radius = 5;
};

using ParticleEvent = std::variant<ParticleDrawEvent>;
