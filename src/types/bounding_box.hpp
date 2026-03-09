#pragma once

#include "backend/types/vec.hpp"

class BoundingBox
{
  public:
    enum class Side
    {
        Left,
        Right,
        Top,
        Bottom
    };

    enum class Corner
    {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

  public:
    BoundingBox() = default;

    void setSize(int width, int height)
    {
        m_size = Vec2<unsigned int>(width, height);
        m_area = width * height;
        m_a = -(m_size / 2.0f).toGrid();
        m_b = m_a + (m_size.toInt()) - 1;
    }
    Vec2<unsigned int> getSize() const { return m_size; }
    Vec2<int> getA() const { return m_a; }
    Vec2<int> getB() const { return m_b; }

    int getArea() const { return m_area; }

  private:
    Vec2<unsigned int> m_size = Vec2<unsigned int>(0, 0);
    int m_area = 0;
    Vec2<int> m_a = Vec2<int>(0, 0);
    Vec2<int> m_b = Vec2<int>(0, 0);
};
