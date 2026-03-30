#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle/particle_world.hpp"

class WorldInteractionHandler
{
  public:
    struct TrajectoryCollisionResponse
    {
        Vec2i resolvePosition;
        bool collided = false;
    };

    struct MTVIntersectionResponse
    {
        int left = 0;
        int right = 0;
        int top = 0;
        int bottom = 0;

        int resolveDistance = 0;

        Vec2i moveVector;
    };

    struct StepResponse
    {
        Vec2i moveVector;
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
    calculateWorldIntersection_MTV(Vec2i pos, const ParticleWorld &world);
    Vec2f
    calculateWorldIntersection_averageDirection(Vec2i pos,
                                                const ParticleWorld &world);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectory(Vec2i start, Vec2i end,
                                     const ParticleWorld &world);

    bool againstSolidSurface(Vec2i pos, RectangleSide side,
                             const ParticleWorld &world);
    bool againstSolidCorner(Vec2i pos, RectangleCorner corner,
                            const ParticleWorld &world);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectorySlide(Vec2i start, Vec2i end,
                                          const ParticleWorld &world);

    LocalWorldQuery generateLocalWorldQuery(Vec2i pos,
                                            const ParticleWorld &world);

    StepResponse calculateStep(Vec2i resolvedPosition, Vec2i originalEnd,
                               const ParticleWorld &world);

  private:
    struct StepDirectionalData
    {
        Vec2i sum{};
        int distance = 0;
        bool moved = false;
    };

  private:
    const StaticGridRectangle &r_boundingBox;
};
