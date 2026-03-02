#pragma once

#include "backend/types/vec.hpp"

class Camera
{
  public:
    Camera(Vec2<unsigned int> viewportSize)
    {
        m_fViewportSize.x = viewportSize.x;
        m_fViewportSize.y = viewportSize.y;
    }
    Camera(const Camera &other) = delete;
    Camera &operator=(const Camera &other) = delete;

    void move(float x, float y) { m_position += Vec2<float>(x, y); }
    void setPosition(int x, int y) { m_position = Vec2<int>(x, y).toFloat(); }
    Vec2<int> getPosition() const { return m_position.toGrid(); }

    Vec2<int> viewportToWorld(int x, int y) const
    {
        return (Vec2<float>(x, y) + m_position - m_fViewportSize / 2.0f)
            .toGrid();
    }

    Vec2<int> worldToViewport(float x, float y) const
    {
        return (Vec2<float>(x, y) - m_position + m_fViewportSize / 2.0f)
            .toGrid();
    }

  private:
    Vec2<float> m_position = Vec2<float>(0.0f, 0.0f);

    Vec2<float> m_fViewportSize;
};
