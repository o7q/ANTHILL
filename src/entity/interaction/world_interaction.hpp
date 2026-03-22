#pragma once

#include "math/numbers.hpp"
#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle/particle_handler.hpp"
#include <limits>

class WorldInteractionHandler
{
  public:
    struct TrajectoryCollisionResponse
    {
        Vec2<int> resolvePos = Vec2<int>(0, 0);
        bool collided = false;
    };

    struct MTVIntersectionResponse
    {
        int left = 0;
        int right = 0;
        int top = 0;
        int bottom = 0;

        int resolveDistance = 0;

        Vec2<int> moveVector;
    };

    struct StepResponse
    {
        Vec2<int> moveVector = Vec2<int>(0, 0);
    };

    struct LocalWorldQuery
    {
        int staticSolidCount = 0;
        float staticSolidPercentage = 0.0f;
        int immovableCount = 0;
        float immovablePercentage = 0.0f;
        float relativeDensity = 0.0f;
        float relativeToxicity = 0.0f;
        float relativeHeat = 0.0f;
    };

  public:
    WorldInteractionHandler(const StaticGridRectangle &bb) : r_boundingBox(bb)
    {
    }

    MTVIntersectionResponse
    calculateWorldIntersection_MTV(Vec2<int> pos,
                                   const ParticleHandler &particles);
    Vec2<float> calculateWorldIntersection_averageDirection(
        Vec2<int> pos, const ParticleHandler &particles);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectory(Vec2<int> start, Vec2<int> end,
                                     const ParticleHandler &particles);

    bool againstSolidSurface(Vec2<int> pos, RectangleSide side,
                             const ParticleHandler &particles);
    bool againstSolidCorner(Vec2<int> pos, RectangleCorner corner,
                            const ParticleHandler &particles);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectorySlide(Vec2<int> start, Vec2<int> end,
                                          const ParticleHandler &particles);

    LocalWorldQuery generateLocalWorldQuery(Vec2<int> pos,
                                            const ParticleHandler &particles);

    struct StepDirectionalData
    {
        Vec2<int> sum{};
        int distance = 0;
        bool moved = false;
    };

    Vec2<int> calculateStep(Vec2<int> resolvedPosition, Vec2<int> originalEnd,
                            const ParticleHandler &particles)
    {
        Vec2<int> out;

        int amount = originalEnd.x - resolvedPosition.x;
        int dir = Math::Numbers::sign(amount);

        int maxStepAmount = 3;

        StepDirectionalData stepUpwards;
        StepDirectionalData stepDownwards;

        for (int i = 1; i <= std::abs(amount); ++i)
        {
            int step = i * dir;

            Vec2<int> upwardsCheckPos = {resolvedPosition.x + step,
                                         resolvedPosition.y +
                                             stepUpwards.sum.y};
            Vec2<int> downwardsCheckPos = {resolvedPosition.x + step,
                                           resolvedPosition.y +
                                               stepDownwards.sum.y};

            MTVIntersectionResponse upwardsCheck =
                calculateWorldIntersection_MTV(upwardsCheckPos, particles);

            MTVIntersectionResponse downwardsCheck =
                calculateWorldIntersection_MTV(downwardsCheckPos, particles);

            Vec2<int> upwardsNextPos =
                upwardsCheckPos + Vec2<int>(0, -upwardsCheck.bottom);
            Vec2<int> downwardsNextPos =
                downwardsCheckPos + Vec2<int>(0, downwardsCheck.top);

            if (upwardsCheck.bottom <= maxStepAmount &&
                calculateWorldIntersection_MTV(upwardsNextPos, particles)
                        .resolveDistance == 0)
            {
                stepUpwards.sum.x = step;
                stepUpwards.sum.y -= upwardsCheck.bottom;
                stepUpwards.distance += upwardsCheck.bottom;
                stepUpwards.moved = true;
            }

            if (downwardsCheck.top <= maxStepAmount &&
                calculateWorldIntersection_MTV(downwardsNextPos, particles)
                        .resolveDistance == 0)
            {
                stepDownwards.sum.x = step;
                stepDownwards.sum.y += downwardsCheck.top;
                stepDownwards.distance += downwardsCheck.top;
                stepDownwards.moved = true;
            }
        }

        if (stepUpwards.moved && !stepDownwards.moved)
        {
            out = stepUpwards.sum;
        }
        if (stepDownwards.moved && !stepUpwards.moved)
        {
            out = stepDownwards.sum;
        }
        if (stepUpwards.moved && stepDownwards.moved)
        {
            if (stepUpwards.distance < stepDownwards.distance)
            {
                out = stepUpwards.sum;
            }
            else
            {
                out = stepDownwards.sum;
            }
        }

        return out;
    }

  private:
    const StaticGridRectangle &r_boundingBox;
};
