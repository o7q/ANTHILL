#pragma once

#include "math/vec.hpp"

class IHasHead
{
  public:
    virtual float getLookDirection() = 0;
    virtual Vec2i getHeadOffset() = 0;
};
