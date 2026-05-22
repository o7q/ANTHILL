#include "against.hpp"

bool EntityWorldInteraction::againstSolidSurface(Vec2i pos, const EntityCollider &collider,
                                                 const ParticleHandler &particleHandler, RectangleSide side)
{
    const Vec2i size    = collider.getPrimary().getSize();
    const Vec2i topLeft = pos + collider.getPrimary().getA();

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
        const Vec2i start = Vec2i(topLeft.x, topLeft.y - 1);
        const Vec2i end   = Vec2i(topLeft.x + size.x - 1, topLeft.y - 1);
        particleHandler.query(start, end, query);
    }
    break;
    case RectangleSide::Right:
    {
        const Vec2i start = Vec2i(topLeft.x + size.x, topLeft.y);
        const Vec2i end   = Vec2i(topLeft.x + size.x, topLeft.y + size.y - 1);
        particleHandler.query(start, end, query);
    }
    break;
    case RectangleSide::Bottom:
    {
        const Vec2i start = Vec2i(topLeft.x, topLeft.y + size.y);
        const Vec2i end   = Vec2i(topLeft.x + size.x - 1, topLeft.y + size.y);
        particleHandler.query(start, end, query);
    }
    break;
    case RectangleSide::Left:
    {
        const Vec2i start = Vec2i(topLeft.x - 1, topLeft.y);
        const Vec2i end   = Vec2i(topLeft.x - 1, topLeft.y + size.y - 1);
        particleHandler.query(start, end, query);
    }
    break;
    }

    return collided;
}

bool EntityWorldInteraction::againstSolidCorner(Vec2i pos, const EntityCollider &collider,
                                                const ParticleHandler &particleHandler,
                                                RectangleCorner corner)
{
    const Vec2i size    = collider.getPrimary().getSize().toInt();
    const Vec2i topLeft = pos + collider.getPrimary().getA();

    bool collided = false;
    switch (corner)
    {
    case RectangleCorner::TopLeft:
    {
        if (const Particle *p = particleHandler.getParticles().get({topLeft.x + size.x, topLeft.y - 1}))
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
        if (const Particle *p = particleHandler.getParticles().get({topLeft.x - 1, topLeft.y - 1}))
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
        if (const Particle *p = particleHandler.getParticles().get({topLeft.x - 1, topLeft.y + size.y}))
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
        if (const Particle *p = particleHandler.getParticles().get({topLeft.x + size.x, topLeft.y + size.y}))
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
