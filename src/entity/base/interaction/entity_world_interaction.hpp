#pragma once

#include "backend/types/vec.hpp"
#include "types/bounding_box.hpp"
#include "world/particle/particle_handler.hpp"

class EntityWorldInteractionHandler
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
    EntityWorldInteractionHandler(ParticleHandler &particles, BoundingBox &bb)
        : r_particles(particles), r_boundingBox(bb)
    {
    }

    MTVIntersectionResponse calculateWorldIntersection_MTV(Vec2<int> pos);
    Vec2<float> calculateWorldIntersection_averageDirection(Vec2<int> pos);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectory(Vec2<int> start, Vec2<int> end);

    bool againstSolidSurface(Vec2<int> pos, BoundingBox::Side side);
    bool againstSolidCorner(Vec2<int> pos, BoundingBox::Corner corner);

    StepResponse calculateStepResponse(Vec2<int> pos, Vec2<float> velocity);

    TrajectoryCollisionResponse
    calculateCollisionFromTrajectorySlide(Vec2<int> start, Vec2<int> end);

    LocalWorldQuery generateLocalWorldQuery(Vec2<int> pos);

  private:
    ParticleHandler &r_particles;
    BoundingBox &r_boundingBox;
};
