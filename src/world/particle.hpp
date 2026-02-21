#pragma once

#include "engine/color.hpp"
#include "engine/verlet.hpp"

class Particle
{
  public:
    enum class PhysicsType
    {
        Sand
    };

    void update() {}

    void setColor(Color color) { m_color = color; }
    void setPhysicsType(PhysicsType physicsType)
    {
        m_physicsType = physicsType;
    }

  private:
    Color m_color;
    PhysicsType m_physicsType;
    VerletBody m_verletBody;
};
