#pragma once

#include "backend/utils/vec.hpp"
#include "utils/rectangle.hpp"
#include "world/particle/particle_handler.hpp"

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

        Vec2<int> resolve;
    };

    struct StepResponse
    {
        bool canStep = false;
        Vec2<int> stepPosition = Vec2<int>(0, 0);
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

    StepResponse calculateStepResponse(Vec2<int> pos, Vec2<float> velocity,
                                       const ParticleHandler &particles);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectorySlide(Vec2<int> start, Vec2<int> end,
                                          const ParticleHandler &particles);

    LocalWorldQuery generateLocalWorldQuery(Vec2<int> pos,
                                            const ParticleHandler &particles);

  private:
    const StaticGridRectangle &r_boundingBox;
};
