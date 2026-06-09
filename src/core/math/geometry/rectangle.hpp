#pragma once

#include "core/math/geometry/vec.hpp"
#include <type_traits>

enum class RectangleSide
{
    Left,
    Right,
    Top,
    Bottom
};

enum class RectangleCorner
{
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight
};

template <typename T> class Rectangle
{
  public:
    struct OverlapResult
    {
        bool overlapping = false;
        Vec2<T> amount;
        Vec2<T> direction;
    };

  public:
    Rectangle() = default;
    Rectangle(Vec2<T> pos, Vec2<T> size)
    {
        setPosition(pos);
        setSize(size);
    }

    void setSize(Vec2<T> size)
    {
        m_size = size;
        m_area = size.x * size.y;
        if constexpr (std::is_floating_point<T>::value)
        {
            m_halfSize = m_size / 2.0f;
        }
        else
        {
            m_halfSize = (m_size / 2.0f).toGrid();
        }
        recalculateAB();
    }
    void setPosition(Vec2<T> pos)
    {
        m_position = pos;
        recalculateAB();
    }

    void move(Vec2<T> amount)
    {
        m_position += amount;
        recalculateAB();
    }

    Vec2<T> getPosition() const { return m_position; }

    Vec2<T> getSize() const { return m_size; }
    Vec2<T> getHalfSize() const { return m_halfSize; }
    Vec2<T> getA() const { return m_a; }
    Vec2<T> getB() const { return m_b; }
    T getArea() const { return m_area; }

    bool pointInside(Vec2<T> pos) const
    {
        return pos.x >= m_a.x && pos.x <= m_b.x && pos.y >= m_a.y && pos.y <= m_b.y;
    }

    OverlapResult overlapping(const Rectangle<T> &other) const
    {
        OverlapResult result;

        Vec2<T> otherPos      = other.getPosition();
        Vec2<T> otherHalfSize = other.getHalfSize();
        Vec2<T> delta         = otherPos - m_position;

        result.amount      = otherHalfSize + m_halfSize - delta.abs();
        result.overlapping = result.amount.x > 0 && result.amount.y > 0;
        result.direction   = delta.sign();

        return result;
    }

    bool contains(const Rectangle<T> &other, bool requireInsideBorder = false)
    {
        Vec2<T> otherA = other.getA();
        Vec2<T> otherB = other.getB();
        if (requireInsideBorder)
        {
            return otherA.x > m_a.x && otherA.y > m_a.y && otherB.x < m_b.x && otherB.y < m_b.y;
        }
        else
        {
            return otherA.x >= m_a.x && otherA.y >= m_a.y && otherB.x <= m_b.x && otherB.y <= m_b.y;
        }
    }

  protected:
    void recalculateAB()
    {
        m_a = -m_halfSize + m_position;
        m_b = m_a + m_size - 1;
    }

  protected:
    Vec2<T> m_position;

    Vec2<T> m_size;
    Vec2<T> m_halfSize;
    Vec2<T> m_a, m_b;
    T m_area = 0;
};

using Rectangle_i = Rectangle<int>;
using Rectangle_u = Rectangle<unsigned int>;
using Rectangle_f = Rectangle<float>;
using Rectangle_d = Rectangle<double>;
