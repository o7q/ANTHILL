#pragma once

#include "engine/color.hpp"
#include "engine/verlet.hpp"

class Particle
{
  public:
    enum class PhysicsType
    {
        Sand,
        Water,
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

    bool isAir()
    {
        return m_physicsType == PhysicsType::None &&
               m_matterType == MatterType::Gas;
    }

    VerletBody &getVerlet() { return m_verletBody; }

    void setUpdateSwapID(bool updateSwapID) { m_updateSwapID = updateSwapID; }
    bool getUpdateSwapID() const { return m_updateSwapID; }

  private:
    Color m_color;
    PhysicsType m_physicsType = PhysicsType::None;
    MatterType m_matterType = MatterType::Gas;

    VerletBody m_verletBody;

    int m_updateSwapID = 0;
};
