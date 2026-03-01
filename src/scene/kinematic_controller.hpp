#pragma once

#include "types/physics/semi_implicit_euler.hpp"

class KinematicController : public SemiImplicitEulerBody
{
  public:

  protected:
    Vec2<float> m_drag = Vec2<float>(0.0f, 0.0f);
};