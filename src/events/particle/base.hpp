#pragma once

#include "core/math/geometry/vec.hpp"

enum class ParticleEventType
{
    SetRadius
};

struct ParticleEvent
{
    ParticleEvent(const ParticleEventType type_) : type(type_) {}
    virtual ~ParticleEvent() = default;

    const ParticleEventType type;
    Vec2i position;
};
