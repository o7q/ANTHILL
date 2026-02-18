#pragma once

#include "vec.hpp"

class VerletController
{
  public:
    VerletController() = default;

    void update()
    {
        Vec2<float> temp = m_position;

        m_position.x =
            2.0f * m_position.x - m_positionPrev.x + m_acceleration.x;
        m_position.y =
            2.0f * m_position.y - m_positionPrev.y + m_acceleration.y;

        m_positionPrev = temp;

        m_acceleration = Vec2<float>(0, 0);
    }

    void setAcceleration(Vec2<float> acceleration)
    {
        m_acceleration = acceleration;
    }

    Vec2<float> getPosition() const { return m_position; }

  private:
    Vec2<float> m_position = Vec2<float>(0, 0);
    Vec2<float> m_positionPrev = Vec2<float>(0, 0);
    Vec2<float> m_acceleration = Vec2<float>(0, 0);
};
