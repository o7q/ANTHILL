#pragma once

#include "backend/utils/vec.hpp"
#include "backend/viewport.hpp"

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
    }

    void move(float x, float y) { m_position += Vec2<float>(x, y); }
    void setPosition(int x, int y) { m_position = Vec2<int>(x, y).toFloat(); }
    Vec2<int> getPosition() const { return m_position.toGrid(); }

    Vec2<int> viewportToWorld(int x, int y, const Viewport &viewport) const;
    Vec2<int> worldToViewport(int x, int y, const Viewport &viewport) const;

  private:
    Vec2<float> m_position = {0.0f, 0.0f};

    Vec2<float> m_goal = {0.0f, 0.0f};
    float m_goalSpeed = 0.25f;
};
