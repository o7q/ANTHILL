#pragma once

#include "px/basic_types/rectangle.hpp"
#include <vector>

class EntityCollider
{
  public:
    EntityCollider() = default;

    void addRect(px::Vec2i offset, px::Vec2i size);

    bool pointInsidePrimary(px::Vec2i bodyPos, px::Vec2i point) const;
    bool pointInsideAny(px::Vec2i bodyPos, px::Vec2i point) const;
    bool overlappingAny(px::Vec2i bodyPos, px::Vec2i otherBodyPos, const EntityCollider &other) const;

    px::Rectangle_i getPrimary() const
    {
        if (m_rects.size() == 0)
        {
            return px::Rectangle_i({}, {});
        }

        return m_rects[0];
    }
    const std::vector<px::Rectangle_i> getAll() const { return m_rects; }

  private:
    std::vector<px::Rectangle_i> m_rects;
};
