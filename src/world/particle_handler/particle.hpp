#pragma once

#include "px/basic_types/color.hpp"
#include "px/verlet/verlet.hpp"

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

    enum class MaterialDescriptor
    {
        None,
        Sandy,
        Metallic
    };

  public:
    Particle() = default;

    void setColor(px::Color color) { m_color = color; }
    px::Color getColor() const { return m_color; }

    void setPhysicsType(PhysicsType physicsType) { m_physicsType = physicsType; }
    PhysicsType getPhysicsType() const { return m_physicsType; }

    void setMatterType(MatterType matterType) { m_matterType = matterType; }
    MatterType getMatterType() const { return m_matterType; }

    void setMaterialDescriptor(MaterialDescriptor materialDescriptor)
    {
        m_materialDescriptor = materialDescriptor;
    }
    MaterialDescriptor getMaterialDescriptor() const { return m_materialDescriptor; }

    bool isAir() const { return m_matterType == MatterType::Gas && m_physicsType == PhysicsType::None; }
    bool isSolid() const { return m_matterType == MatterType::Solid; }
    bool isLiquid() const { return m_matterType == MatterType::Liquid; }
    bool isGas() const { return m_matterType == MatterType::Gas; }

    void setRestitution(float restitution) { m_restitution = restitution; }
    float getRestitution() const { return m_restitution; }

    px::VerletBody &getVerlet() { return m_verletBody; }
    const px::VerletBody &getVerlet() const { return m_verletBody; }

    bool isMoving() const
    {
        return m_verletBody.getPosition().toGrid() != m_verletBody.getPreviousPosition().toGrid();
    }

    void setMass(float mass) { m_mass = mass; }
    float getMass() const { return m_mass; }

    void setHardness(int hardness) { m_hardness = hardness; }
    int getHardness() const { return m_hardness; }

  private:
    px::Color m_color;
    PhysicsType m_physicsType               = PhysicsType::None;
    MatterType m_matterType                 = MatterType::Gas;
    MaterialDescriptor m_materialDescriptor = MaterialDescriptor::None;

    px::VerletBody m_verletBody;
    float m_restitution = 0.0f;
    float m_mass        = 1.0f;

    int m_hardness = 0;
};
