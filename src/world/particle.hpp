#pragma once

#include "engine/color.hpp"
#include "engine/verlet.hpp"

class Particle
{
  public:
    enum class PhysicsType
    {
        Sand,
        None
    };

    enum class MatterType
    {
        Solid,
        Liquid,
        Gas
    };

  public:
    Particle() = default;

    void setColor(Color color) { m_color = color; }
    Color getColor() const { return m_color; }

    void setPhysicsType(PhysicsType physicsType)
    {
        m_physicsType = physicsType;
    }
    PhysicsType getPhysicsType() const { return m_physicsType; }

    void setMatterType(MatterType matterType) { m_matterType = matterType; }
    MatterType getMatterType() const { return m_matterType; }

    VerletBody &getVerlet() { return m_verletBody; }

  private:
    Color m_color;
    PhysicsType m_physicsType = PhysicsType::None;
    MatterType m_matterType = MatterType::Gas;

    VerletBody m_verletBody;
};
