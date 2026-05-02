#pragma once

#include "math/verlet/verlet.hpp"
#include <cstdint>

class VerletLink
{
  public:
    VerletLink(uint32_t i1, uint32_t i2) : m_i1(i1), m_i2(i2) {}

    void update(VerletBody &v1, VerletBody &v2)
    {
        Vec2f v1_pos = v1.getPosition();
        Vec2f v2_pos = v2.getPosition();

        Vec2f delta  = v1_pos - v2_pos;
        float dist   = delta.length();
        float diff   = m_distance - dist;
        Vec2f normal = delta / dist;

        if (!m_pinI1)
        {
            v1.setPositionPresent(v1_pos + normal * diff * 0.5f * m_stiffness);
        }
        if (!m_pinI2)
        {
            v2.setPositionPresent(v2_pos - normal * diff * 0.5f * m_stiffness);
        }
    }

    void setDistance(float distance) { m_distance = distance; }
    void setStiffness(float stiffness) { m_stiffness = stiffness; }
    void pinI1(bool value) { m_pinI1 = value; }
    void pinI2(bool value) { m_pinI2 = value; }

    int getI1() const { return m_i1; }
    int getI2() const { return m_i2; }

  private:
    uint32_t m_i1 = 0;
    bool m_pinI1  = false;
    uint32_t m_i2 = 0;
    bool m_pinI2  = false;

    float m_distance  = 1.0f;
    float m_stiffness = 1.0f;
};
