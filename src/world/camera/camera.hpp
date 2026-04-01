#pragma once

#include "backend/viewport/viewport.hpp"
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

    void clearGoal() { m_goalSet = false; }

    void setPosition(Vec2i pos) { m_position = pos.toFloat(); }
    Vec2i getPosition() const { return m_position.toGrid(); }

    Vec2i viewportToWorld(Vec2i pos, const Viewport &viewport) const;
    Vec2i worldToViewport(Vec2i pos, const Viewport &viewport) const;

  private:
    Vec2f m_position;

    Vec2i m_goal;
    bool m_goalSet = false;
    float m_goalSpeed = 0.15f;
};
