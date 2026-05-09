#include "body_update_handler.hpp"

#include "core/math/rectangle.hpp"
#include "entity/world_interaction/against.hpp"
#include "entity/world_interaction/step.hpp"
#include "entity/world_interaction/trajectory.hpp"

void BodyUpdateHandler::update(const EntityUpdateContext &context)
{
    Vec2f currentPos = r_body.getPositionFloat();
    apply_external_forces(currentPos.toGrid(), context);
    r_body.update(context.time.dt);
    Vec2f updatedPos = r_body.getPositionFloat();

    prevent_world_collision(currentPos, updatedPos, context);
}

void BodyUpdateHandler::apply_external_forces(Vec2i currentPos, const EntityUpdateContext &context)
{
    if (EntityWorldInteraction::againstSolidSurface(currentPos, r_boundingBox, context.particleHandler,
                                                    RectangleSide::Bottom))
    {
        r_body.haltMotionInDirection({0, 1});
    }
    else
    {
        r_body.applyGravity();
    }

    if (EntityWorldInteraction::againstSolidSurface(currentPos, r_boundingBox, context.particleHandler,
                                                    RectangleSide::Top))
    {
        r_body.haltMotionInDirection({0, -1});
    }
}

void BodyUpdateHandler::prevent_world_collision(Vec2f currentPos, Vec2f updatedPos,
                                                const EntityUpdateContext &context)
{
    EntityWorldInteraction::TrajectoryCollisionResponse response =
        EntityWorldInteraction::calculateCollisionFromTrajectorySlide(
            currentPos.toGrid(), updatedPos.toGrid(), r_boundingBox, context.particleHandler);

    if (response.collided)
    {
        Vec2f remainder = updatedPos - updatedPos.floor();

        EntityWorldInteraction::StepResponse step = EntityWorldInteraction::calculateStep(
            response.resolvePosition, updatedPos.toGrid(), r_boundingBox, context.particleHandler);

        Vec2f finalPos = response.resolvePosition.toFloat() + step.moveVector.toFloat() + remainder;

        r_body.setPositionFloat(finalPos);
    }
}
