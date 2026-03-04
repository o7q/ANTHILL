#pragma once

#include "types/physics/semi_implicit_euler.hpp"

class KinematicBody : public SemiImplicitEulerBody
{
  public:
    void haltMotionInDirection(int dirX, int dirY);

    bool horizontallyInMotion() { return std::abs(m_velocity.x) > 0.001f; }
    bool verticallyInMotion() { return std::abs(m_velocity.y) > 0.001f; }
};
