#pragma once

#include "backend/utils/vec.hpp"

class PhysicsBody
{
  public:
    virtual void integrate(float dt) = 0;

  protected:
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);
};
