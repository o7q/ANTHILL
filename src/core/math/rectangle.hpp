#pragma once

#include "core/math/vec.hpp"

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

    bool overlapping(const GridRectangle &other) const
    {
        Vec2i otherA = other.getA();
        Vec2i otherB = other.getB();
        return m_b.x >= otherA.x && m_a.x <= otherB.x && m_b.y >= otherA.y && m_a.y <= otherB.y;
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
