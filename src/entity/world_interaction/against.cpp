#include "against.hpp"

bool EntityWorldInteraction::againstSolidSurface(Vec2i pos, const StaticGridRectangle &boundingBox,
                                                 const ParticleHandler &particleHandler, RectangleSide side)
{
    Vec2u size    = boundingBox.getSize();
    Vec2i topLeft = pos + boundingBox.getA();

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
        Vec2i end   = Vec2i(topLeft.x + size.x - 1, topLeft.y - 1);
        particleHandler.query(start, end, query);
    }
    break;
    case RectangleSide::Right:
    {
        Vec2i start = Vec2i(topLeft.x + size.x, topLeft.y);
        Vec2i end   = Vec2i(topLeft.x + size.x, topLeft.y + size.y - 1);
        particleHandler.query(start, end, query);
    }
    break;
    case RectangleSide::Bottom:
    {
        Vec2i start = Vec2i(topLeft.x, topLeft.y + size.y);
        Vec2i end   = Vec2i(topLeft.x + size.x - 1, topLeft.y + size.y);
        particleHandler.query(start, end, query);
    }
    break;
    case RectangleSide::Left:
    {
        Vec2i start = Vec2i(topLeft.x - 1, topLeft.y);
        Vec2i end   = Vec2i(topLeft.x - 1, topLeft.y + size.y - 1);
        particleHandler.query(start, end, query);
    }
    break;
    }

    return collided;
}

bool EntityWorldInteraction::againstSolidCorner(Vec2i pos, const StaticGridRectangle &boundingBox,
                                                const ParticleHandler &particleHandler,
                                                RectangleCorner corner)
{
    Vec2i size    = boundingBox.getSize().toInt();
    Vec2i topLeft = pos + boundingBox.getA();

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
