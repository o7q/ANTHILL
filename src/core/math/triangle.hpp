#pragma once

#include "core/math/circle.hpp"
#include "core/math/vec.hpp"
#include <cmath>

template <typename T> class Triangle2
{
  public:
    void setV0(Vec2<T> v)
    {
        return m_v[0] = v;
        recalculate_area();
    }
    void setV1(Vec2<T> v)
    {
        return m_v[1] = v;
        recalculate_area();
    }
    void setV2(Vec2<T> v)
    {
        return m_v[2] = v;
        recalculate_area();
    }
    void setVertices(Vec2<T> v0, Vec2<T> v1, Vec2<T> v2)
    {
        m_v[0] = v0;
        m_v[1] = v1;
        m_v[2] = v2;
        recalculate_area();
    }

    const Vec2<T> getV0() const { return m_v[0]; }
    const Vec2<T> getV1() const { return m_v[1]; }
    const Vec2<T> getV2() const { return m_v[2]; }

    const Vec2<T> *getVertices() const { return m_v; }

    Circle2f calculateCircumcircle()
    {
        // https://en.wikipedia.org/wiki/Circumcircle#Cartesian_coordinates_2
        Vec2i a = m_v[0];
        Vec2i b = m_v[1];
        Vec2i c = m_v[2];

        int axsq = a.x * a.x;
        int aysq = a.y * a.y;
        int bxsq = b.x * b.x;
        int bysq = b.y * b.y;
        int cxsq = c.x * c.x;
        int cysq = c.y * c.y;

        float d = 2 * (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
        float x =
            ((axsq + aysq) * (b.y - c.y) + (bxsq + bysq) * (c.y - a.y) + (cxsq + cysq) * (a.y - b.y)) / d;
        float y =
            ((axsq + aysq) * (c.x - b.x) + (bxsq + bysq) * (a.x - c.x) + (cxsq + cysq) * (b.x - a.x)) / d;

        float dx = x - a.x;
        float dy = y - a.y;
        float r  = std::sqrt(dx * dx + dy * dy);

        Circle2f out;
        out.pos    = {x, y};
        out.radius = r;
        return out;
    }

    float getArea() const { return m_area; }

  private:
    void recalculate_area()
    {
        // heron's formula
        float a = (m_v[0] - m_v[1]).length();
        float b = (m_v[1] - m_v[2]).length();
        float c = (m_v[2] - m_v[0]).length();
        float s = (a + b + c) / 2.0f;
        m_area  = std::sqrt(s * (s - a) * (s - b) * (s - c));
    }

  private:
    Vec2<T> m_v[3];
    float m_area = 0.0f;
};

using Triangle2i = Triangle2<int>;
using Triangle2u = Triangle2<unsigned int>;
using Triangle2f = Triangle2<float>;
using Triangle2d = Triangle2<double>;
