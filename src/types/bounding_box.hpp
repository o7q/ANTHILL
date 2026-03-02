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

  public:
    BoundingBox() {}

    void setSize(int width, int height) { m_size = Vec2<int>(width, height); }
    Vec2<int> getSize() const { return m_size; }
    Vec2<int> getA() const { return -(m_size / 2.0f).toGrid(); }
    Vec2<int> getB() const { return getA() + m_size - 1; }

  private:
    Vec2<int> m_size = Vec2<int>(0, 0);
};
