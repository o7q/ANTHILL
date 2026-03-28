#pragma once

class IDirectional
{
  public:
    float getAngle() const { return m_angle; }

  protected:
    float m_angle = 0.0f;
};
