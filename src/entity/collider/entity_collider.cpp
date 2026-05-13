#include "entity_collider.hpp"

void EntityCollider::addRect(Vec2i offset, Vec2u size) { m_rects.push_back(GridRectangle(offset, size)); }

bool EntityCollider::pointInsidePrimary(Vec2i bodyPos, Vec2i point) const
{
    if (m_rects.size() == 0)
    {
        return false;
    }

    GridRectangle rect = m_rects[0];
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

    for (GridRectangle rect : m_rects)
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
    for (GridRectangle rect : m_rects)
    {
        rect.setPosition(rect.getPosition() + bodyPos);
        for (GridRectangle otherRect : other.getAll())
        {
            otherRect.setPosition(otherRect.getPosition() + otherBodyPos);
            if (rect.overlapping(otherRect))
            {
                return true;
            }
        }
    }

    return false;
}
