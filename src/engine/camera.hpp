#pragma once

#include "engine/vec.hpp"

class Camera
{
  public:
    Camera() = default;

    void move(float x, float y) { m_position += Vec2<float>(x, y); }
    void setPosition(float x, float y) { m_position = Vec2<float>(x, y); }
    Vec2<float> getPosition() const { return m_position; }

  private:
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);
};
