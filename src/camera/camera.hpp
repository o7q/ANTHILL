#pragma once

#include "../math/vector.hpp"

class Camera
{
public:
    void setPosition(int x, int y);

    void move(int x, int y);

    Vec2<int> transformPoint(Vec2<int> point) const;
    Vec2<int> transformPoint(int x, int y) const;

    Vec2<int> getPosition() const { return m_position; }

private:
    Vec2<int> m_position;
};