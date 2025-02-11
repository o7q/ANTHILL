#pragma once

#include "../math/vector.hpp"

class Camera
{
public:
    Camera(int window_width, int window_height)
    {
        m_window_size.x = window_width;
        m_window_size.y = window_height;
    }

    void update(float dt);

    void setPosition(float x, float y);
    void move(float x, float y);
    void setGoal(float x, float y);

    Vec2<int> transformPoint(float x, float y) const;

    Vec2<int> getPosition() const { return Vec2<int>(m_position.x, m_position.y); }

private:
    void update_goal(float dt);

private:
    Vec2<float> m_position;
    Vec2<int> m_window_size;

    Vec2<float> m_goal_position;
    bool m_has_goal = false;
    const float m_goal_speed = 0.125f;
};