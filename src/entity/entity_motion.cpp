#include "entity.hpp"

void Entity::updateApplyExternalMotion(EntityUpdateContext &context)
{
    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Bottom, context.particles))
    {
        m_body.haltMotionInDirection(0, 1);
    }
    else
    {
        m_body.applyGravity();
    }

    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Top, context.particles))
    {
        m_body.haltMotionInDirection(0, -1);
    }
}

void Entity::updateMotion(EntityUpdateContext &context)
{
    updateApplyExternalMotion(context);

    Vec2<int> currentPos = m_body.getPosition();
    Vec2<float> velocity = m_body.getVelocity();
    WorldInteractionHandler::LocalWorldQuery worldQuery =
        m_interactionBox.getWorldHandler().generateLocalWorldQuery(
            currentPos, context.particles);

    if (worldQuery.staticSolidCount == 0)
    {
        currentPos = updateMotion_step(currentPos, velocity, context);
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

Vec2<int> Entity::updateMotion_step(Vec2<int> currentPos, Vec2<float> velocity,
                                    EntityUpdateContext &context)
{
    WorldInteractionHandler::StepResponse stepResponse =
        m_interactionBox.getWorldHandler().calculateStepResponse(
            currentPos, velocity, context.particles);

    if (stepResponse.canStep)
    {
        m_body.setPosition(stepResponse.stepPosition.x,
                           stepResponse.stepPosition.y);
        currentPos = stepResponse.stepPosition;
    }

    return currentPos;
}

void Entity::updateMotion_moveAndPreventWorldCollision(
    Vec2<int> currentPos, EntityUpdateContext &context)
{
    m_body.update(context.dt);
    Vec2<int> endPos = m_body.getPosition();

    WorldInteractionHandler::TrajectoryCollisionResponse response =
        m_interactionBox.getWorldHandler()
            .calculateCollisionFromTrajectorySlide(currentPos, endPos,
                                                   context.particles);

    if (response.collided)
    {
        m_body.setPosition(response.resolvePos.x, response.resolvePos.y);
    }
}
