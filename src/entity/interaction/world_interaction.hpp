#pragma once

#include "math/rectangle.hpp"
#include "math/vec.hpp"
#include "world/particle/particle_handler.hpp"

class WorldInteractionHandler
{
  public:
    struct TrajectoryCollisionResponse
    {
        Vec2i resolvePosition = Vec2i(0, 0);
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
        Vec2i moveVector = Vec2i(0, 0);
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
    calculateWorldIntersection_MTV(Vec2i pos, const ParticleHandler &particles);
    Vec2f calculateWorldIntersection_averageDirection(
        Vec2i pos, const ParticleHandler &particles);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectory(Vec2i start, Vec2i end,
                                     const ParticleHandler &particles);

    bool againstSolidSurface(Vec2i pos, RectangleSide side,
                             const ParticleHandler &particles);
    bool againstSolidCorner(Vec2i pos, RectangleCorner corner,
                            const ParticleHandler &particles);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectorySlide(Vec2i start, Vec2i end,
                                          const ParticleHandler &particles);

    LocalWorldQuery generateLocalWorldQuery(Vec2i pos,
                                            const ParticleHandler &particles);

    StepResponse calculateStep(Vec2i resolvedPosition, Vec2i originalEnd,
                               const ParticleHandler &particles);

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
