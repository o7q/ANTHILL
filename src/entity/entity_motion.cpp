#include "entity.hpp"

void Entity::handleMotion()
{
    if (m_worldCollisionHandler.againstSolidSurface(
            m_kinematicController.getPosition(), BoundingBox::Side::Bottom))
    {
        m_kinematicController.haltMotionInDirection(0, 1);
    }
    else
    {
        m_kinematicController.applyGravity();
    }

    if (m_worldCollisionHandler.againstSolidSurface(
            m_kinematicController.getPosition(), BoundingBox::Side::Top))
    {
        m_kinematicController.haltMotionInDirection(0, -1);
    }
}
