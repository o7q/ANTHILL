#include "intersection.hpp"

EntityWorldInteraction::MTVIntersectionResponse
EntityWorldInteraction::calculateWorldIntersection_MTV(px::Vec2i pos, const EntityCollider &collider,
                                                       const ParticleHandler &particleHandler)
{
    const px::Vec2i size    = collider.getPrimary().getSize().toGrid();
    const px::Vec2i topLeft = collider.getPrimary().getA() + pos;

    //    0
    // 3 [-] 1
    //    2
    bool collisionOccurred          = false;
    std::array<int, 4> intersection = {0, 0, 0, 0};
    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            px::Vec2i worldPos = topLeft + px::Vec2i(x, y);

            const Particle *p = particleHandler.getParticles().get(worldPos);
            if (!p || (p->isSolid() && !p->isMoving()))
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
    response.top        = intersection[0];
    response.right      = intersection[1];
    response.bottom     = intersection[2];
    response.left       = intersection[3];
    response.moveVector = px::Vec2i(0, 0);

    if (!collisionOccurred)
    {
        return response;
    }

    int lowest = std::numeric_limits<int>::max();
    int side   = -1;

    for (int i = 0; i < 4; ++i)
    {
        if (intersection[i] < lowest)
        {
            lowest = intersection[i];
            side   = i;
        }
    }

    switch (side)
    {
    case 0:
        response.moveVector = px::Vec2i(0, lowest);
        break;
    case 1:
        response.moveVector = px::Vec2i(-lowest, 0);
        break;
    case 2:
        response.moveVector = px::Vec2i(0, -lowest);
        break;
    case 3:
        response.moveVector = px::Vec2i(lowest, 0);
        break;
    }

    response.resolveDistance = lowest;

    return response;
}

px::Vec2f EntityWorldInteraction::calculateWorldIntersection_averageDirection(
    px::Vec2i pos, const EntityCollider &collider, const ParticleHandler &particleHandler)
{
    const px::Vec2i size    = collider.getPrimary().getSize();
    const px::Vec2i topLeft = pos + collider.getPrimary().getA();

    px::Vec2i sum = px::Vec2i(0, 0);
    int count = 0;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            px::Vec2i worldPos = topLeft + px::Vec2i(x, y);

            const Particle *p = particleHandler.getParticles().get(worldPos);
            if (!p || (p->isSolid() && !p->isMoving()))
            {
                sum += (pos - worldPos);
                ++count;
            }
        }
    }

    if (count == 0)
    {
        return px::Vec2f(0, 0);
    }

    return (sum.toFloat() / count).normalize();
}
