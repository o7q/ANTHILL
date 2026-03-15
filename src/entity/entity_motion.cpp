#include "entity.hpp"

void Entity::applyExternalMotion()
{
    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Bottom))
    {
        m_body.haltMotionInDirection(0, 1);
    }
    else
    {
        m_body.applyGravity();
    }

    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            m_body.getPosition(), BoundingBox::Side::Top))
    {
        m_body.haltMotionInDirection(0, -1);
    }
}

void Entity::updateMotion(float dt)
{
    applyExternalMotion();

    Vec2<int> currentPos = m_body.getPosition();
    Vec2<float> velocity = m_body.getVelocity();
    WorldInteractionHandler::LocalWorldQuery worldQuery =
        m_interactionBox.getWorldHandler().generateLocalWorldQuery(currentPos);

    if (worldQuery.staticSolidCount == 0)
    {
        currentPos = updateMotion_step(currentPos, velocity);
        updateMotion_moveAndPreventWorldCollision(currentPos, dt);
    }
    else
    {
        WorldInteractionHandler::MTVIntersectionResponse response =
            m_interactionBox.getWorldHandler().calculateWorldIntersection_MTV(
                currentPos);

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

Vec2<int> Entity::updateMotion_step(Vec2<int> currentPos, Vec2<float> velocity)
{
    WorldInteractionHandler::StepResponse stepResponse =
        m_interactionBox.getWorldHandler().calculateStepResponse(currentPos,
                                                                 velocity);

    if (stepResponse.canStep)
    {
        m_body.setPosition(stepResponse.stepPosition.x,
                           stepResponse.stepPosition.y);
        currentPos = stepResponse.stepPosition;
    }

    return currentPos;
}

void Entity::updateMotion_moveAndPreventWorldCollision(Vec2<int> currentPos,
                                                       float dt)
{
    m_body.update(dt);
    Vec2<int> endPos = m_body.getPosition();

    WorldInteractionHandler::TrajectoryCollisionResponse response =
        m_interactionBox.getWorldHandler()
            .calculateCollisionFromTrajectorySlide(currentPos, endPos);

    if (response.collided)
    {
        m_body.setPosition(response.resolvePos.x, response.resolvePos.y);
    }
}
