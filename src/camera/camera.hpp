#pragma once

#include "px/math/angle.hpp"
#include "px/math/geometry/vec.hpp"
#include "px/time/time_handler.hpp"

class Camera
{
  public:
    Camera()          = default;
    virtual ~Camera() = default;

    void update(TimeHandler::Info time);

    void setGoal(Vec2i pos)
    {
        m_goal    = pos;
        m_goalSet = true;
    }

    void setViewSize(Vec2u size) { m_viewSize = size; }
    Vec2u getViewSize() const { return m_viewSize; }

    void clearGoal() { m_goalSet = false; }

    void setPosition(Vec2i pos) { m_position = pos.toFloat(); }
    Vec2i getPosition() const { return m_position.toGrid(); }

    Vec2i viewportToCamera(Vec2i pos) const;
    Vec2i cameraToViewport(Vec2i pos) const;

    void jerk(Angle angle, float amount);

  private:
    Vec2f m_position;
    Vec2u m_viewSize;

    Vec2i m_goal;
    bool m_goalSet = false;
};
