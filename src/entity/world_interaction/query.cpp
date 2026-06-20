#include "query.hpp"

EntityWorldInteraction::LocalWorldQuery
EntityWorldInteraction::generateLocalWorldQuery(px::Vec2i pos, const EntityCollider &collider,
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

    particleHandler.query(collider.getPrimary().getA() + pos, collider.getPrimary().getB() + pos, query);

    return out;
}
