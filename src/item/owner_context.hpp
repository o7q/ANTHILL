#pragma once

#include "events/entity/base.hpp"
#include "events/event_emitter.hpp"
#include "math/vec.hpp"
#include <cstdint>

struct ItemOwnerContext
{
    uint64_t id = 0;
    EventEmitter<EntityEvent> &eventEmitter;
    Vec2i pos;
    float angle = 0.0f;
};
