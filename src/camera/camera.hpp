#pragma once

#include "../math/vector.hpp"

class Camera
{
public:
    void setPosition(Vec2<float> position);

    void move(float x, float y);

    Vec2<float> transformPoint(Vec2<float> point) const;
    Vec2<float> transformPoint(float x, float y) const;

    Vec2<float> getPosition() const { return m_position; }

private:
    Vec2<float> m_position;
};