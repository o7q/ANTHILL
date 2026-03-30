#include "math/rectangle.hpp"
#include "world_interaction.hpp"

bool WorldInteractionHandler::againstSolidSurface(
    Vec2i pos, RectangleSide side, const ParticleHandler &particles)
{
    Vec2u size = r_boundingBox.getSize();
    Vec2i topLeft = pos + r_boundingBox.getA();

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
        Vec2i start = Vec2i(topLeft.x, topLeft.y - 1);
        Vec2i end = Vec2i(topLeft.x + size.x - 1, topLeft.y - 1);
        particles.query(start, end, query);
    }
    break;
    case RectangleSide::Right:
    {
        Vec2i start = Vec2i(topLeft.x + size.x, topLeft.y);
        Vec2i end = Vec2i(topLeft.x + size.x, topLeft.y + size.y - 1);
        particles.query(start, end, query);
    }
    break;
    case RectangleSide::Bottom:
    {
        Vec2i start = Vec2i(topLeft.x, topLeft.y + size.y);
        Vec2i end = Vec2i(topLeft.x + size.x - 1, topLeft.y + size.y);
        particles.query(start, end, query);
    }
    break;
    case RectangleSide::Left:
    {
        Vec2i start = Vec2i(topLeft.x - 1, topLeft.y);
        Vec2i end = Vec2i(topLeft.x - 1, topLeft.y + size.y - 1);
        particles.query(start, end, query);
    }
    break;
    }

    return collided;
}

bool WorldInteractionHandler::againstSolidCorner(
    Vec2i pos, RectangleCorner corner, const ParticleHandler &particles)
{
    Vec2u size = r_boundingBox.getSize();
    Vec2i topLeft = pos + r_boundingBox.getA();

    bool collided = false;
    switch (corner)
    {
    case RectangleCorner::TopLeft:
    {
        if (const Particle *p = particles.getRawParticles().get(
                topLeft.x + size.x, topLeft.y - 1))
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
                particles.getRawParticles().get(topLeft.x - 1, topLeft.y - 1))
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
        if (const Particle *p = particles.getRawParticles().get(
                topLeft.x - 1, topLeft.y + size.y))
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
        if (const Particle *p = particles.getRawParticles().get(
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

WorldInteractionHandler::LocalWorldQuery
WorldInteractionHandler::generateLocalWorldQuery(
    Vec2i pos, const ParticleHandler &particles)
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
