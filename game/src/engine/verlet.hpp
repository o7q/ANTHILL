#pragma once

#include "vec.hpp"

struct VerletWorldProperties
{
    VerletWorldProperties() = default;
    Vec2<float> air_resistance = Vec2<float>(0.0f, 0.0f);
};

class VerletBody
{
  public:
    VerletBody() = default;
    VerletBody(const VerletBody &other) = delete;
    VerletBody &operator=(const VerletBody &other) = delete;

    void update(float dt)
    {
        Vec2<float> velocity = m_position - m_positionPrev;
        Vec2<float> acceleration = m_force / m_mass;

        Vec2<float> damp = Vec2<float>(1.0f, 1.0f);
        if (p_world_properties)
        {
            damp.x = 1.0f / (p_world_properties->air_resistance.x + 1.0f);
            damp.y = 1.0f / (p_world_properties->air_resistance.y + 1.0f);
        }

        m_positionPrev = m_position;
        m_position += velocity * damp + acceleration * dt * dt;
    }

    void setForce(Vec2<float> force) { m_force = force; }
    void setMass(float mass) { m_mass = mass; }
    void setWorldProperties(VerletWorldProperties *world_properties)
    {
        p_world_properties = world_properties;
    }

    Vec2<float> getPosition() const { return m_position; }

  private:
    float m_mass = 1.0f;
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_positionPrev = Vec2<float>(0.0f, 0.0f);
    Vec2<float> m_force = Vec2<float>(0.0f, 0.0f);

    VerletWorldProperties *p_world_properties = nullptr;
};
