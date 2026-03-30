#pragma once

class IDirectional
{
  public:
    virtual float getAngle() const { return m_angle; }
    virtual void setAngle(float angle) { m_angle = angle; }

  protected:
    float m_angle = 0.0f;
};
