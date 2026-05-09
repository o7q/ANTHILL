#pragma once

#include "core/math/color.hpp"
#include "core/math/verlet/verlet.hpp"

class Particle
{
  public:
    enum class PhysicsType
    {
        Sand,
        Sandstone,
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

    void setPhysicsType(PhysicsType physicsType) { m_physicsType = physicsType; }
    PhysicsType getPhysicsType() const { return m_physicsType; }

    void setMatterType(MatterType matterType) { m_matterType = matterType; }
    MatterType getMatterType() const { return m_matterType; }

    bool isBlank() const
    {
        return m_physicsType == PhysicsType::None && m_matterType == MatterType::Gas && m_color.a == 0;
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
        return m_verletBody.getPosition().toGrid() != m_verletBody.getPreviousPosition().toGrid();
    }

    void setMass(float mass) { m_mass = mass; }
    float getMass() const { return m_mass; }

  private:
    Color m_color;
    PhysicsType m_physicsType = PhysicsType::None;
    MatterType m_matterType   = MatterType::Gas;

    VerletBody m_verletBody;
    float m_restitution = 0.0f;
    float m_mass        = 1.0f;

    bool m_updateSwapID = 0;
};
