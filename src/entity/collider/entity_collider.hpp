#pragma once

#include "core/math/geometry/rectangle.hpp"
#include <vector>

class EntityCollider
{
  public:
    EntityCollider() = default;

    void addRect(Vec2i offset, Vec2u size);

    bool pointInsidePrimary(Vec2i bodyPos, Vec2i point) const;
    bool pointInsideAny(Vec2i bodyPos, Vec2i point) const;
    bool overlappingAny(Vec2i bodyPos, Vec2i otherBodyPos, const EntityCollider &other) const;

    GridRectangle getPrimary() const
    {
        if (m_rects.size() == 0)
        {
            return GridRectangle({}, {});
        }

        return m_rects[0];
    }
    const std::vector<GridRectangle> getAll() const { return m_rects; }

  private:
    std::vector<GridRectangle> m_rects;
};
