#pragma once

#include "px/basic_types/vec.hpp"

enum class ParticleEventType
{
    SetRadius,
    ApplyForce
};

struct ParticleEvent
{
    ParticleEvent(const ParticleEventType type_) : type(type_) {}
    virtual ~ParticleEvent() = default;

    const ParticleEventType type;
    px::Vec2i position;
};
