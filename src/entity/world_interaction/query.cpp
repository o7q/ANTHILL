#include "query.hpp"

EntityWorldInteraction::LocalWorldQuery
EntityWorldInteraction::generateLocalWorldQuery(
    Vec2i pos, const StaticGridRectangle &boundingBox,
    const ParticleHandler &particleHandler)
{
    LocalWorldQuery out;

    auto query = [&](const Particle *p)
    {
        if (p->isSolid() && !p->isMoving())
        {
            out.staticSolidCount++;
        }

        return false;
    };

    particleHandler.query(boundingBox.getA() + pos, boundingBox.getB() + pos,
                          query);

    return out;
}
