#pragma once

#include "math/vec.hpp"

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

class StaticGridRectangle
{
  public:
    StaticGridRectangle() = default;

    void setSize(Vec2u size)
    {
        m_size     = size;
        m_area     = size.x * size.y;
        m_halfSize = (m_size / 2.0f).toGrid().toUnsignedInt();
        recalculateAB();
    }
    Vec2u getSize() const { return m_size; }
    Vec2u getHalfSize() const { return m_halfSize; }
    Vec2i getA() const { return m_a; }
    Vec2i getB() const { return m_b; }
    int getArea() const { return m_area; }

    virtual bool pointInside(Vec2i pos) const
    {
        return pos.x >= m_a.x && pos.x <= m_b.x && pos.y >= m_a.y && pos.y <= m_b.y;
    }

  protected:
    virtual void recalculateAB()
    {
        m_a = -(m_halfSize.toInt());
        m_b = m_a + (m_size.toInt()) - 1;
    }

  protected:
    Vec2u m_size;
    Vec2u m_halfSize;
    Vec2i m_a;
    Vec2i m_b;
    int m_area = 0;
};

class PositionalGridRectangle : public StaticGridRectangle
{
  public:
    void setPosition(Vec2i pos)
    {
        m_position = pos;
        recalculateAB();
    }

    Vec2i getPosition() const { return m_position; }

  protected:
    virtual void recalculateAB() override
    {
        m_a = -(m_halfSize.toInt()) + m_position;
        m_b = m_a + (m_size.toInt()) - 1;
    }

    Vec2i m_position;
};
