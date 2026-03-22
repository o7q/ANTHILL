#include "entity.hpp"
#include "math/rectangle.hpp"

void Entity::updateApplyExternalMotion(EntityUpdateContext &context)
{
    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), RectangleSide::Bottom, context.particles))
    {
        m_body.haltMotionInDirection(0, 1);
    }
    else
    {
        m_body.applyGravity();
    }

    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), RectangleSide::Top, context.particles))
    {
        m_body.haltMotionInDirection(0, -1);
    }
}

void Entity::updateMotion(EntityUpdateContext &context)
{
    updateApplyExternalMotion(context);

    Vec2<int> currentPos = m_body.getPosition();
    WorldInteractionHandler::LocalWorldQuery worldQuery =
        m_interactionBox.getWorldHandler().generateLocalWorldQuery(
            currentPos, context.particles);

    if (worldQuery.staticSolidCount == 0)
    {
        updateMotion_moveAndPreventWorldCollision(currentPos, context);
    }
    else
    {
        WorldInteractionHandler::MTVIntersectionResponse response =
            m_interactionBox.getWorldHandler().calculateWorldIntersection_MTV(
                currentPos, context.particles);

        if (response.resolveDistance <= 2)
        {
            m_body.setPosition(response.resolve.x + currentPos.x,
                               response.resolve.y + currentPos.y);
        }
        else
        {
        }
    }
}

void Entity::updateMotion_moveAndPreventWorldCollision(
    Vec2<int> currentPos, EntityUpdateContext &context)
{
    m_body.update(context.dt);
    Vec2<int> updatedPos = m_body.getPosition();

    WorldInteractionHandler::TrajectoryCollisionResponse response =
        m_interactionBox.getWorldHandler()
            .calculateCollisionFromTrajectorySlide(currentPos, updatedPos,
                                                   context.particles);

    if (response.collided)
    {
        m_body.setPosition(response.resolvePos.x, response.resolvePos.y);
    }
}
