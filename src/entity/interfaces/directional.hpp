#pragma once

#include "math/vec.hpp"

class IDirectional
{
  public:
    float getLookAngle() const { return m_lookAngle; }
    Vec2i getLookPosition() const { return m_lookPosition; }

  protected:
    float m_lookAngle = 0.0f;
    Vec2i m_lookPosition;
};
