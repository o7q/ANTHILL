#pragma once

#include "engine/vec.hpp"

struct VerletWorldProperties
{
    VerletWorldProperties() = default;
    Vec2<float> air_resistance = Vec2<float>(0.0f, 0.0f);
};

class VerletBody
{
  public:
    VerletBody() = default;

    void update(float dt);

    void setForce(float x, float y)
    {
        m_force = Vec2<float>(x, y);
        m_forcesApplied = true;
    }
    void clearForces()
    {
        m_force = Vec2<float>(0.0f, 0.0f);
        m_forcesApplied = false;
    }
    void setMass(float mass) { m_mass = mass; }
    void setWorldProperties(VerletWorldProperties *world_properties)
    {
        p_world_properties = world_properties;
    }

    void setPosition(float x, float y)
    {
        m_position = Vec2<float>(x, y);
        m_positionPrev = Vec2<float>(x, y);
    }

    Vec2<float> getPosition() const { return m_position; }
    bool areForcesApplied() const { return m_forcesApplied; }

  private:
    float m_mass = 1.0f;
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_positionPrev = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);
    bool m_forcesApplied = false;

    VerletWorldProperties *p_world_properties = nullptr;
};
