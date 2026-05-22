#pragma once

#include "core/math/geometry/vec.hpp"

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

class GridRectangle
{
  public:
    struct OverlapResult
    {
        bool overlapping = false;
        Vec2i amount;
        Vec2i direction;
    };

  public:
    GridRectangle() = default;
    GridRectangle(Vec2i pos, Vec2u size)
    {
        setPosition(pos);
        setSize(size);
    }

    void setSize(Vec2u size)
    {
        m_size     = size;
        m_area     = size.x * size.y;
        m_halfSize = (m_size / 2.0f).toGrid().toUnsignedInt();
        recalculateAB();
    }
    void setPosition(Vec2i pos)
    {
        m_position = pos;
        recalculateAB();
    }

    void move(Vec2i amount)
    {
        m_position += amount;
        recalculateAB();
    }

    Vec2i getPosition() const { return m_position; }

    Vec2u getSize() const { return m_size; }
    Vec2u getHalfSize() const { return m_halfSize; }
    Vec2i getA() const { return m_a; }
    Vec2i getB() const { return m_b; }
    int getArea() const { return m_area; }

    bool pointInside(Vec2i pos) const
    {
        return pos.x >= m_a.x && pos.x <= m_b.x && pos.y >= m_a.y && pos.y <= m_b.y;
    }

    OverlapResult overlapping(const GridRectangle &other) const
    {
        OverlapResult result;

        Vec2i otherPos      = other.getPosition();
        Vec2i otherHalfSize = other.getHalfSize().toInt();
        Vec2i delta         = otherPos - m_position;

        result.amount      = otherHalfSize + m_halfSize.toInt() - delta.abs();
        result.overlapping = result.amount.x > 0 && result.amount.y > 0;
        result.direction   = delta.sign();

        return result;
    }

    bool contains(const GridRectangle &other)
    {
        Vec2i otherA = other.getA();
        Vec2i otherB = other.getB();
        return otherA.x >= m_a.x && otherA.y >= m_a.y && otherB.x <= m_b.x && otherB.y <= m_b.y;
    }

  protected:
    void recalculateAB()
    {
        m_a = -(m_halfSize.toInt()) + m_position;
        m_b = m_a + (m_size.toInt()) - 1;
    }

  protected:
    Vec2i m_position;

    Vec2u m_size;
    Vec2u m_halfSize;
    Vec2i m_a;
    Vec2i m_b;
    int m_area = 0;
};
