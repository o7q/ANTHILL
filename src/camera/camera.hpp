#pragma once

#include "px/basic_types/angle.hpp"
#include "px/basic_types/vec.hpp"
#include "px/time/time_handler.hpp"

class Camera
{
  public:
    Camera()          = default;
    virtual ~Camera() = default;

    void update(const px::TimeHandler &time);

    void setGoal(px::Vec2i pos)
    {
        m_goal    = pos;
        m_goalSet = true;
    }

    void setViewSize(px::Vec2u size) { m_viewSize = size; }
    px::Vec2u getViewSize() const { return m_viewSize; }

    void clearGoal() { m_goalSet = false; }

    void setPosition(px::Vec2i pos) { m_position = pos.toFloat(); }
    px::Vec2i getPosition() const { return m_position.toGrid(); }

    px::Vec2i viewportToCamera(px::Vec2i pos) const;
    px::Vec2i cameraToRenderer(px::Vec2i pos) const;

    void jerk(px::Angle_f angle, float amount);

  private:
    px::Vec2f m_position;
    px::Vec2u m_viewSize;

    px::Vec2i m_goal;
    bool m_goalSet = false;
};
