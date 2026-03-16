#include "utils/rectangle.hpp"
#include "world_interaction.hpp"

bool WorldInteractionHandler::againstSolidSurface(
    Vec2<int> pos, RectangleSide side, const ParticleHandler &particles)
{
    Vec2<unsigned int> size = r_boundingBox.getSize();
    Vec2<int> topLeft = pos + r_boundingBox.getA();

    bool collided = false;

    auto query = [&](const Particle *p)
    {
        if (p->isSolid() && !p->isMoving())
        {
            collided = true;
            return true;
        }
        return false;
    };

    switch (side)
    {
    case RectangleSide::Top:
    {
        Vec2<int> start = Vec2<int>(topLeft.x, topLeft.y - 1);
        Vec2<int> end = Vec2<int>(topLeft.x + size.x - 1, topLeft.y - 1);
        particles.query(start, end, query);
    }
    break;
    case RectangleSide::Right:
    {
        Vec2<int> start = Vec2<int>(topLeft.x + size.x, topLeft.y);
        Vec2<int> end = Vec2<int>(topLeft.x + size.x, topLeft.y + size.y - 1);
        particles.query(start, end, query);
    }
    break;
    case RectangleSide::Bottom:
    {
        Vec2<int> start = Vec2<int>(topLeft.x, topLeft.y + size.y);
        Vec2<int> end = Vec2<int>(topLeft.x + size.x - 1, topLeft.y + size.y);
        particles.query(start, end, query);
    }
    break;
    case RectangleSide::Left:
    {
        Vec2<int> start = Vec2<int>(topLeft.x - 1, topLeft.y);
        Vec2<int> end = Vec2<int>(topLeft.x - 1, topLeft.y + size.y - 1);
        particles.query(start, end, query);
    }
    break;
    }

    return collided;
}

bool WorldInteractionHandler::againstSolidCorner(
    Vec2<int> pos, RectangleCorner corner, const ParticleHandler &particles)
{
    Vec2<unsigned int> size = r_boundingBox.getSize();
    Vec2<int> topLeft = pos + r_boundingBox.getA();

    bool collided = false;
    switch (corner)
    {
    case RectangleCorner::TopLeft:
    {
        if (const Particle *p =
                particles.getParticles().get(topLeft.x + size.x, topLeft.y - 1))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    case RectangleCorner::TopRight:
    {
        if (const Particle *p =
                particles.getParticles().get(topLeft.x - 1, topLeft.y - 1))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    case RectangleCorner::BottomLeft:
    {
        if (const Particle *p =
                particles.getParticles().get(topLeft.x - 1, topLeft.y + size.y))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    case RectangleCorner::BottomRight:
    {
        if (const Particle *p = particles.getParticles().get(
                topLeft.x + size.x, topLeft.y + size.y))
        {
            if (p->isSolid() && !p->isMoving())
            {
                collided = true;
            }
        }
    }
    break;
    }

    return collided;
}

WorldInteractionHandler::StepResponse
WorldInteractionHandler::calculateStepResponse(Vec2<int> pos,
                                               Vec2<float> velocity,
                                               const ParticleHandler &particles)
{
    StepResponse out;
    out.stepPosition = pos;
    bool blockedLeft = againstSolidSurface(pos, RectangleSide::Left, particles);
    bool blockedRight =
        againstSolidSurface(pos, RectangleSide::Right, particles);

    if ((blockedLeft && velocity.x < 0.0f) ||
        (blockedRight && velocity.x > 0.0f))
    {
        for (int step = 1; step <= 3; ++step)
        {
            Vec2<int> steppedPos = {pos.x, pos.y - step};

            bool stillBlockedRight =
                blockedRight &&
                againstSolidSurface(steppedPos, RectangleSide::Right,
                                    particles);
            bool stillBlockedLeft =
                blockedLeft &&
                againstSolidSurface(steppedPos, RectangleSide::Left, particles);

            if (!stillBlockedRight && !stillBlockedLeft)
            {
                WorldInteractionHandler::TrajectoryCollisionResponse
                    collisionCheck = calculateCollisionFromTrajectory(
                        pos, steppedPos, particles);
                if (collisionCheck.collided)
                {
                    break;
                }
                out.stepPosition = steppedPos;
                out.canStep = true;
                blockedRight = false;
                blockedLeft = false;
                break;
            }
        }
    }

    return out;
}

WorldInteractionHandler::LocalWorldQuery
WorldInteractionHandler::generateLocalWorldQuery(
    Vec2<int> pos, const ParticleHandler &particles)
{
    LocalWorldQuery out;

    auto query = [&](const Particle *p)
    {
        if (p->isSolid() && !p->isMoving())
        {
            out.staticSolidCount++;
        }

        if (p->isImmovable())
        {
            out.immovableCount++;
        }

        out.relativeDensity += p->getDensity();

        return false;
    };

    int area = r_boundingBox.getArea();
    out.relativeDensity /= area;
    out.relativeToxicity /= area;
    out.relativeHeat /= area;
    out.staticSolidPercentage = static_cast<float>(out.staticSolidCount) / area;
    out.immovablePercentage = static_cast<float>(out.immovableCount) / area;

    particles.query(r_boundingBox.getA() + pos, r_boundingBox.getB() + pos,
                    query);

    return out;
}
