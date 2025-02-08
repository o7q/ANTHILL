#pragma once

#include "../math/vector.hpp"

struct BoundingBox
{
    BoundingBox() = default;
    BoundingBox(int x, int y, int width, int height);

    void setPosition(int x, int y);
    void setSize(int width, int height);

    Vec2<int> getPosition() const { return m_pos; }
    Vec2<int> getSize() const { return m_size; }

    Vec2<int> getP1() const { return m_points[0]; }
    Vec2<int> getP2() const { return m_points[1]; }
    Vec2<int> getP3() const { return m_points[2]; }
    Vec2<int> getP4() const { return m_points[3]; }

private:
    void update_points();

private:
    Vec2<int> m_pos;
    Vec2<int> m_size;

    Vec2<int> m_points[4];
};