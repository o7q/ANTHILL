#include "entity.hpp"
#include "entity/interaction/world_interaction.hpp"
#include "math/rectangle.hpp"

void Entity::updateMotion_applyExternal(Vec2i currentPos,
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
    Vec2f currentPos = m_body.getPositionFloat();
    updateMotion_applyExternal(currentPos.toGrid(), context);
    m_body.update(context.dt);
    Vec2f updatedPos = m_body.getPositionFloat();

    updateMotion_preventWorldCollision(currentPos, updatedPos, context);
}

void Entity::updateMotion_preventWorldCollision(
    Vec2f currentPos, Vec2f updatedPos, const EntityUpdateContext &context)
{
    WorldInteractionHandler::TrajectoryCollisionResponse response =
        m_interactionBox.getWorldHandler()
            .calculateCollisionFromTrajectorySlide(
                currentPos.toGrid(), updatedPos.toGrid(), context.particles);

    if (response.collided)
    {
        float remainderX = updatedPos.x - std::floor(updatedPos.x);
        float remainderY = updatedPos.y - std::floor(updatedPos.y);

        WorldInteractionHandler::StepResponse step =
            m_interactionBox.getWorldHandler().calculateStep(
                response.resolvePosition, updatedPos.toGrid(),
                context.particles);

        float finalX =
            response.resolvePosition.x + step.moveVector.x + remainderX;
        float finalY =
            response.resolvePosition.y + step.moveVector.y + remainderY;

        m_body.setPositionFloat(finalX, finalY);
    }
}
