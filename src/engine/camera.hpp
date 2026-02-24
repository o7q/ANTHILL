#pragma once

#include "engine/backend/types/vec.hpp"

class Camera
{
  public:
    Camera(Vec2<unsigned int> viewportSize)
    {
        m_viewportSize.x = viewportSize.x;
        m_viewportSize.y = viewportSize.y;
    }

    void move(float x, float y) { m_position += Vec2<float>(x, y); }
    void setPosition(float x, float y) { m_position = Vec2<float>(x, y); }
    Vec2<float> getPosition() const { return m_position; }

    Vec2<float> transformViewportPosition(float x, float y) const
    {
        return Vec2<float>(x, y) + m_position - m_viewportSize / 2.0f;
    }

  private:
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);

    Vec2<float> m_viewportSize;
};
