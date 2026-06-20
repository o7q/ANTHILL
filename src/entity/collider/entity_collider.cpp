#include "entity_collider.hpp"

void EntityCollider::addRect(px::Vec2i offset, px::Vec2i size) { m_rects.push_back(px::Rectangle_i(offset, size)); }

bool EntityCollider::pointInsidePrimary(px::Vec2i bodyPos, px::Vec2i point) const
{
    if (m_rects.size() == 0)
    {
        return false;
    }

    px::Rectangle_i rect = m_rects[0];
    rect.setPosition(rect.getPosition() + bodyPos);
    if (rect.pointInside(point))
    {
        return true;
    }

    return false;
}

bool EntityCollider::pointInsideAny(px::Vec2i bodyPos, px::Vec2i point) const
{
    if (m_rects.size() == 0)
    {
        return false;
    }

    for (px::Rectangle_i rect : m_rects)
    {
        rect.setPosition(rect.getPosition() + bodyPos);

        if (rect.pointInside(point))
        {
            return true;
        }
    }

    return false;
}

bool EntityCollider::overlappingAny(px::Vec2i bodyPos, px::Vec2i otherBodyPos, const EntityCollider &other) const
{
    for (px::Rectangle_i rect : m_rects)
    {
        rect.setPosition(rect.getPosition() + bodyPos);
        for (px::Rectangle_i otherRect : other.getAll())
        {
            otherRect.setPosition(otherRect.getPosition() + otherBodyPos);
            if (rect.overlapping(otherRect).overlapping)
            {
                return true;
            }
        }
    }

    return false;
}
