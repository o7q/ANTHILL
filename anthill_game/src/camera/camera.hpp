#pragma once

#include "../math/vector.hpp"

class Camera
{
public:
    void setPosition(float x, float y);

    void move(float x, float y);

    Vec2<int> transformPoint(float x, float y) const;

    Vec2<int> getPosition() const { return Vec2<int>(m_position.x, m_position.y); }

private:
    Vec2<float> m_position;
};