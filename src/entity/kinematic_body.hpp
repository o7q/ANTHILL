#pragma once

#include "types/physics/semi_implicit_euler.hpp"

class KinematicBody : public SemiImplicitEulerBody
{
  public:
    void haltMotionInDirection(int dirX, int dirY);
};
