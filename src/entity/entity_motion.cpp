#include "entity.hpp"
#include "entity/interaction/world_interaction.hpp"
#include "math/rectangle.hpp"

void Entity::updateApplyExternalMotion(Vec2<int> currentPos,
                                       const EntityUpdateContext &context)
{
    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            currentPos, RectangleSide::Bottom, context.particles))
    {
        m_body.haltMotionInDirection(0, 1);
    }
    else
    {
        m_body.applyGravity();
    }

    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            currentPos, RectangleSide::Top, context.particles))
    {
        m_body.haltMotionInDirection(0, -1);
    }
}

void Entity::updateMotion(const EntityUpdateContext &context)
{
    Vec2<float> currentPos = m_body.getPositionFloat();
    updateApplyExternalMotion(currentPos.toGrid(), context);

    updateMotion_moveAndPreventWorldCollision(currentPos, context);
}

void Entity::updateMotion_moveAndPreventWorldCollision(
    Vec2<float> currentPos, const EntityUpdateContext &context)
{
    m_body.update(context.dt);
    Vec2<float> updatedPos = m_body.getPositionFloat();

    WorldInteractionHandler::TrajectoryCollisionResponse response =
        m_interactionBox.getWorldHandler()
            .calculateCollisionFromTrajectorySlide(
                currentPos.toGrid(), updatedPos.toGrid(), context.particles);

    if (response.collided)
    {
        float remainderX = updatedPos.x - std::floor(updatedPos.x);
        float remainderY = updatedPos.y - std::floor(updatedPos.y);

        Vec2<int> step = m_interactionBox.getWorldHandler().calculateStep(
            response.resolvePos, updatedPos.toGrid(), context.particles);

        float finalX = response.resolvePos.x + step.x + remainderX;
        float finalY = response.resolvePos.y + step.y + remainderY;

        m_body.setPositionFloat(finalX, finalY);
    }
}
