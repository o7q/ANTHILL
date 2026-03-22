#pragma once

#include "backend/viewport/viewport.hpp"
#include "math/vec.hpp"

class Camera
{
  public:
    Camera() = default;
    virtual ~Camera() = default;

    void update(float dt);

    void setGoal(float x, float y)
    {
        m_goal.x = x;
        m_goal.y = y;
        m_goalSet = true;
    }

    void clearGoal() { m_goalSet = false; }

    void move(float x, float y) { m_position += Vec2f(x, y); }
    void setPosition(int x, int y) { m_position = Vec2i(x, y).toFloat(); }
    Vec2i getPosition() const { return m_position.toGrid(); }

    Vec2i viewportToWorld(int x, int y, const Viewport &viewport) const;
    Vec2i worldToViewport(int x, int y, const Viewport &viewport) const;

  private:
    Vec2f m_position = {0.0f, 0.0f};

    Vec2f m_goal = {0.0f, 0.0f};
    bool m_goalSet = false;
    float m_goalSpeed = 0.25f;
};
