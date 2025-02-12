#pragma once

#include "../math/vector.hpp"

struct BoundingBox
{
    BoundingBox() = default;
    BoundingBox(float x, float y, float width, float height);

    void setPosition(float x, float y);
    void setSize(float width, float height);

    Vec2<float> getPosition() const { return m_pos; }
    Vec2<float> getSize() const { return m_size; }

    Vec2<float> getP1() const { return m_points[0]; }
    Vec2<float> getP2() const { return m_points[1]; }
    Vec2<float> getP3() const { return m_points[2]; }
    Vec2<float> getP4() const { return m_points[3]; }

private:
    void update_points();

private:
    Vec2<float> m_pos;
    Vec2<float> m_size;

    Vec2<float> m_points[4];
};