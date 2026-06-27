#include "step.hpp"
#include "entity/world_interaction/intersection.hpp"

EntityWorldInteraction::StepResponse
EntityWorldInteraction::calculateStep(px::Vec2i resolvedPosition, px::Vec2i originalEnd,
                                      const EntityCollider &collider, const ParticleHandler &particleHandler)
{
    StepResponse response;

    const int amount = originalEnd.x - resolvedPosition.x;
    const int dir    = px::Numbers::sign(amount);

    const int maxStepAmount = 4;

    StepDirectionalData stepUpwards;
    StepDirectionalData stepDownwards;

    for (int i = 1; i <= std::abs(amount); ++i)
    {
        int step = i * dir;

        px::Vec2i upwardsCheckPos   = {resolvedPosition.x + step, resolvedPosition.y + stepUpwards.sum.y};
        px::Vec2i downwardsCheckPos = {resolvedPosition.x + step, resolvedPosition.y + stepDownwards.sum.y};

        MTVIntersectionResponse upwardsCheck =
            calculateWorldIntersection_MTV(upwardsCheckPos, collider, particleHandler);

        MTVIntersectionResponse downwardsCheck =
            calculateWorldIntersection_MTV(downwardsCheckPos, collider, particleHandler);

        px::Vec2i upwardsNextPos   = upwardsCheckPos + px::Vec2i{0, -upwardsCheck.bottom};
        px::Vec2i downwardsNextPos = downwardsCheckPos + px::Vec2i{0, downwardsCheck.top};

        if (upwardsCheck.bottom <= maxStepAmount &&
            calculateWorldIntersection_MTV(upwardsNextPos, collider, particleHandler).resolveDistance == 0)
        {
            stepUpwards.sum.x = step;
            stepUpwards.sum.y -= upwardsCheck.bottom;
            stepUpwards.distance += upwardsCheck.bottom;
            stepUpwards.moved = true;
        }

        if (downwardsCheck.top <= maxStepAmount &&
            calculateWorldIntersection_MTV(downwardsNextPos, collider, particleHandler).resolveDistance == 0)
        {
            stepDownwards.sum.x = step;
            stepDownwards.sum.y += downwardsCheck.top;
            stepDownwards.distance += downwardsCheck.top;
            stepDownwards.moved = true;
        }
    }

    if (stepUpwards.moved && !stepDownwards.moved)
    {
        response.moveVector = stepUpwards.sum;
    }
    if (stepDownwards.moved && !stepUpwards.moved)
    {
        response.moveVector = stepDownwards.sum;
    }
    if (stepUpwards.moved && stepDownwards.moved)
    {
        if (stepUpwards.distance < stepDownwards.distance)
        {
            response.moveVector = stepUpwards.sum;
        }
        else
        {
            response.moveVector = stepDownwards.sum;
        }
    }

    return response;
}
