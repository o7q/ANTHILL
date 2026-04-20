#pragma once

#include "math/vec.hpp"

class Camera
{
  public:
    Camera() = default;
    virtual ~Camera() = default;

    void update(float dt);

    void setGoal(Vec2i pos)
    {
        m_goal = pos;
        m_goalSet = true;
    }

    void setViewSize(Vec2u size) { m_viewSize = size; }
    Vec2u getViewSize() const { return m_viewSize; }

    void clearGoal() { m_goalSet = false; }

    void setPosition(Vec2i pos) { m_position = pos.toFloat(); }
    Vec2i getPosition() const { return m_position.toGrid(); }

    Vec2i viewportToCamera(Vec2i pos) const;
    Vec2i cameraToViewport(Vec2i pos) const;

    void jerk(float angle, float amount);

  private:
    Vec2f m_position;
    Vec2u m_viewSize;

    float m_dtAvg = 0.0f;

    Vec2i m_goal;
    bool m_goalSet = false;
    float m_goalSpeed = 1.0f;
};
