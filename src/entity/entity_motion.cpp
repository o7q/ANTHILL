#include "entity.hpp"

void Entity::handleMotion()
{
    if (m_worldCollisionHandler.againstSolidSurface(m_body.getPosition(),
                                                    BoundingBox::Side::Bottom))
    {
        m_body.haltMotionInDirection(0, 1);
    }
    else
    {
        m_body.applyGravity();
    }

    if (m_worldCollisionHandler.againstSolidSurface(m_body.getPosition(),
                                                    BoundingBox::Side::Top))
    {
        m_body.haltMotionInDirection(0, -1);
    }
}
