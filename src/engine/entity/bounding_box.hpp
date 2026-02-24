#pragma once

#include "engine/backend/types/vec.hpp"

class BoundingBox
{
  public:
    BoundingBox() {}

    void setSize(Vec2<float> size) { m_size = size; }
    Vec2<float> getSize() const { return m_size; }
    Vec2<float> getA() const { return Vec2<float>(0, 0) - m_size / 2.0f; }
    Vec2<float> getB() const { return Vec2<float>(0, 0) + m_size / 2.0f; }

  private:
    Vec2<float> m_size;
};
