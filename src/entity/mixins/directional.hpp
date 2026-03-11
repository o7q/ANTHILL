#pragma once

class IDirectional
{
  public:
    float getLookAngle() const { return m_lookAngle; }

  protected:
    float m_lookAngle = 0.0f;
};
