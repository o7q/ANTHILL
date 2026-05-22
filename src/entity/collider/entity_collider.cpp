#include "entity_collider.hpp"

void EntityCollider::addRect(Vec2i offset, Vec2i size) { m_rects.push_back(Rectangle_i(offset, size)); }

bool EntityCollider::pointInsidePrimary(Vec2i bodyPos, Vec2i point) const
{
    if (m_rects.size() == 0)
    {
        return false;
    }

    Rectangle_i rect = m_rects[0];
    rect.setPosition(rect.getPosition() + bodyPos);
    if (rect.pointInside(point))
    {
        return true;
    }

    return false;
}

bool EntityCollider::pointInsideAny(Vec2i bodyPos, Vec2i point) const
{
    if (m_rects.size() == 0)
    {
        return false;
    }

    for (Rectangle_i rect : m_rects)
    {
        rect.setPosition(rect.getPosition() + bodyPos);

        if (rect.pointInside(point))
        {
            return true;
        }
    }

    return false;
}

bool EntityCollider::overlappingAny(Vec2i bodyPos, Vec2i otherBodyPos, const EntityCollider &other) const
{
    for (Rectangle_i rect : m_rects)
    {
        rect.setPosition(rect.getPosition() + bodyPos);
        for (Rectangle_i otherRect : other.getAll())
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
