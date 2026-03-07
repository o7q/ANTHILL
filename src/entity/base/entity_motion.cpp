#include "entity.hpp"

void Entity::handleMotion()
{
    if (m_collisionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Bottom))
    {
        m_body.haltMotionInDirection(0, 1);
    }
    else
    {
        m_body.applyGravity();
    }

    if (m_collisionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Top))
    {
        m_body.haltMotionInDirection(0, -1);
    }
    
    if (m_collisionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Left))
    {
        m_body.haltMotionInDirection(-1, 0);
    }

    if (m_collisionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Right))
    {
        m_body.haltMotionInDirection(1, 0);
    }
}
