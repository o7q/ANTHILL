#include "intersection.hpp"

EntityWorldInteraction::MTVIntersectionResponse
EntityWorldInteraction::calculateWorldIntersection_MTV(
    Vec2i pos, const StaticGridRectangle &boundingBox,
    const ParticleHandler &particleHandler)
{
    const Vec2i size = boundingBox.getSize().toGrid();
    const Vec2i topLeft = boundingBox.getA() + pos;

    //    0
    // 3 [-] 1
    //    2
    bool collisionOccurred = false;
    std::array<int, 4> intersection = {0, 0, 0, 0};
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Vec2i worldPos = topLeft + Vec2i(x, y);

            const Particle *p = particleHandler.getParticles().get(worldPos);

            if (!p)
            {
                continue;
            }

            if (p->isSolid() && !p->isMoving())
            {
                intersection[0] = std::max(intersection[0], y + 1);
                intersection[1] = std::max(intersection[1], size.x - x);
                intersection[2] = std::max(intersection[2], size.y - y);
                intersection[3] = std::max(intersection[3], x + 1);

                collisionOccurred = true;
            }
        }
    }

    MTVIntersectionResponse response;
    response.top = intersection[0];
    response.right = intersection[1];
    response.bottom = intersection[2];
    response.left = intersection[3];
    response.moveVector = Vec2i(0, 0);

    if (!collisionOccurred)
    {
        return response;
    }

    int lowest = std::numeric_limits<int>::max();
    int side = -1;

    for (int i = 0; i < 4; ++i)
    {
        if (intersection[i] < lowest)
        {
            lowest = intersection[i];
            side = i;
        }
    }

    switch (side)
    {
    case 0:
        response.moveVector = Vec2i(0, lowest);
        break;
    case 1:
        response.moveVector = Vec2i(-lowest, 0);
        break;
    case 2:
        response.moveVector = Vec2i(0, -lowest);
        break;
    case 3:
        response.moveVector = Vec2i(lowest, 0);
        break;
    }

    response.resolveDistance = lowest;

    return response;
}

Vec2f EntityWorldInteraction::calculateWorldIntersection_averageDirection(
    Vec2i pos, const StaticGridRectangle &boundingBox,
    const ParticleHandler &particleHandler)
{
    const Vec2u size = boundingBox.getSize();
    const Vec2i topLeft = pos + boundingBox.getA();

    Vec2i sum = Vec2i(0, 0);
    int count = 0;

    for (unsigned int y = 0; y < size.y; ++y)
    {
        for (unsigned int x = 0; x < size.x; ++x)
        {
            Vec2i worldPos = topLeft + Vec2i(x, y);

            const Particle *p = particleHandler.getParticles().get(worldPos);
            if (!p)
            {
                continue;
            }

            if (p->isSolid())
            {
                sum += (pos - worldPos);
                ++count;
            }
        }
    }

    if (count == 0)
    {
        return Vec2f(0, 0);
    }

    return (sum.toFloat() / count).normalize();
}
