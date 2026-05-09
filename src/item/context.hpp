#pragma once

#include "core/math/vec.hpp"
#include <cstdint>

struct ItemUseContext
{
    uint64_t ownerID = 0;
    Vec2i heldPosition;
    float heldAngle = 0.0f;
};
