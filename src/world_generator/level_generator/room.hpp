#pragma once

#include "core/math/geometry/vec.hpp"

class Room
{
  public:
    Room() = default;
    Room(Vec2i size) { m_size = size; }

    Vec2i getSize() const { return m_size; }

  protected:
    Vec2i m_size;
};
