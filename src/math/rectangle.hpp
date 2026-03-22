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

    void setSize(unsigned int width, unsigned int height)
    {
        m_size = Vec2u(width, height);
        m_area = width * height;
        m_halfSize = (m_size / 2.0f).toGrid().toUnsignedInt();
        recalculateAB();
    }
    Vec2u getSize() const { return m_size; }
    Vec2u getHalfSize() const { return m_halfSize; }
    Vec2i getA() const { return m_a; }
    Vec2i getB() const { return m_b; }
    int getArea() const { return m_area; }

    virtual bool pointInside(int x, int y) const
    {
        return x >= m_a.x && x <= m_b.x && y >= m_a.y && y <= m_b.y;
    }

  protected:
    virtual void recalculateAB()
    {
        m_a = -(m_halfSize.toInt());
        m_b = m_a + (m_size.toInt()) - 1;
    }

  protected:
    Vec2u m_size = Vec2u(0, 0);
    Vec2u m_halfSize = Vec2u(0, 0);
    int m_area = 0;
    Vec2i m_a = Vec2i(0, 0);
    Vec2i m_b = Vec2i(0, 0);
};

class GridRectangle : public StaticGridRectangle
{
  public:
    void setPosition(int x, int y)
    {
        m_position.x = x;
        m_position.y = y;
        recalculateAB();
    }

  protected:
    virtual void recalculateAB() override
    {
        m_a = -(m_halfSize.toInt()) + m_position;
        m_b = m_a + (m_size.toInt()) - 1;
    }

    Vec2i m_position;
};
