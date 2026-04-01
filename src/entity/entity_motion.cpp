#include "entity.hpp"
#include "entity/interaction/world_interaction.hpp"
#include "math/rectangle.hpp"

void Entity::updateMotion_applyExternal(Vec2i currentPos,
                                        const EntityUpdateContext &context)
{
    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            currentPos, RectangleSide::Bottom, context.world))
    {
        m_body.haltMotionInDirection({0, 1});
    }
    else
    {
        m_body.applyGravity();
    }

    if (m_interactionBox.getWorldHandler().againstSolidSurface(
            currentPos, RectangleSide::Top, context.world))
    {
        m_body.haltMotionInDirection({0, -1});
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
                currentPos.toGrid(), updatedPos.toGrid(), context.world);

    if (response.collided)
    {
        Vec2f remainder = updatedPos - updatedPos.floor();

        WorldInteractionHandler::StepResponse step =
            m_interactionBox.getWorldHandler().calculateStep(
                response.resolvePosition, updatedPos.toGrid(), context.world);

        Vec2f finalPos = response.resolvePosition.toFloat() +
                         step.moveVector.toFloat() + remainder;

        m_body.setPositionFloat(finalPos);
    }
}
