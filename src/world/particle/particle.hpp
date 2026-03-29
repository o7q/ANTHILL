#pragma once

#include "math/color.hpp"
#include "math/physics/verlet.hpp"

class Particle
{
  public:
    enum class PhysicsType
    {
        Sand,
        Water,
        Smoke,
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

    bool isAir() const
    {
        return m_physicsType == PhysicsType::None &&
               m_matterType == MatterType::Gas;
    }
    bool isSolid() const { return m_matterType == MatterType::Solid; }
    bool isLiquid() const { return m_matterType == MatterType::Liquid; }
    bool isGas() const { return m_matterType == MatterType::Gas; }

    void setRestitution(float restitution) { m_restitution = restitution; }
    float getRestitution() const { return m_restitution; }

    VerletBody &getVerlet() { return m_verletBody; }

    void setUpdateSwapID(bool updateSwapID) { m_updateSwapID = updateSwapID; }
    bool getUpdateSwapID() const { return m_updateSwapID; }

    bool isMoving() const
    {
        return m_verletBody.getPosition() != m_verletBody.getPreviousPosition();
    }

    void setImmovable(bool immovable) { m_immovable = immovable; }
    bool isImmovable() const { return m_immovable; }

    void setDensity(float density) { m_density = density; }
    float getDensity() const { return m_density; }

  private:
    Color m_color;
    PhysicsType m_physicsType = PhysicsType::None;
    MatterType m_matterType = MatterType::Gas;

    VerletBody m_verletBody;
    float m_restitution = 1.0f;
    float m_density = 0.0f;

    bool m_immovable = false;

    bool m_updateSwapID = 0;
};
