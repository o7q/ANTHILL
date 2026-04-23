#pragma once

#include "math/vec.hpp"

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
