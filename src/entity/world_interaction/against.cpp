#include "against.hpp"

bool EntityWorldInteraction::againstSolidSurface(px::Vec2i pos, const EntityCollider &collider,
                                                 const ParticleHandler &particleHandler,
                                                 px::RectangleSide side)
{
    const px::Vec2i size    = collider.getPrimary().getSize();
    const px::Vec2i topLeft = pos + collider.getPrimary().getA();

    bool collided = false;

    auto query = [&](const Particle *p)
    {
        if (!p || (p->isSolid() && !p->isMoving()))
        {
            collided = true;
            return true;
        }
        return false;
    };

    switch (side)
    {
    case px::RectangleSide::Top:
    {
        const px::Vec2i start = px::Vec2i{topLeft.x, topLeft.y - 1};
        const px::Vec2i end   = px::Vec2i{topLeft.x + size.x - 1, topLeft.y - 1};
        particleHandler.query(start, end, query, false);
    }
    break;
    case px::RectangleSide::Right:
    {
        const px::Vec2i start = px::Vec2i{topLeft.x + size.x, topLeft.y};
        const px::Vec2i end   = px::Vec2i{topLeft.x + size.x, topLeft.y + size.y - 1};
        particleHandler.query(start, end, query, false);
    }
    break;
    case px::RectangleSide::Bottom:
    {
        const px::Vec2i start = px::Vec2i{topLeft.x, topLeft.y + size.y};
        const px::Vec2i end   = px::Vec2i{topLeft.x + size.x - 1, topLeft.y + size.y};
        particleHandler.query(start, end, query, false);
    }
    break;
    case px::RectangleSide::Left:
    {
        const px::Vec2i start = px::Vec2i{topLeft.x - 1, topLeft.y};
        const px::Vec2i end   = px::Vec2i{topLeft.x - 1, topLeft.y + size.y - 1};
        particleHandler.query(start, end, query, false);
    }
    break;
    }

    return collided;
}

bool EntityWorldInteraction::againstSolidCorner(px::Vec2i pos, const EntityCollider &collider,
                                                const ParticleHandler &particleHandler,
                                                px::RectangleCorner corner)
{
    const px::Vec2i size    = collider.getPrimary().getSize().toInt();
    const px::Vec2i topLeft = pos + collider.getPrimary().getA();

    bool collided = false;
    switch (corner)
    {
    case px::RectangleCorner::TopLeft:
    {
        const Particle *p = particleHandler.getParticles().get({topLeft.x + size.x, topLeft.y - 1});
        if (!p || (p->isSolid() && !p->isMoving()))
        {
            collided = true;
        }
    }
    break;
    case px::RectangleCorner::TopRight:
    {
        const Particle *p = particleHandler.getParticles().get({topLeft.x - 1, topLeft.y - 1});
        if (!p || (p->isSolid() && !p->isMoving()))
        {
            collided = true;
        }
    }
    break;
    case px::RectangleCorner::BottomLeft:
    {
        const Particle *p = particleHandler.getParticles().get({topLeft.x - 1, topLeft.y + size.y});
        if (!p || (p->isSolid() && !p->isMoving()))
        {
            collided = true;
        }
    }
    break;
    case px::RectangleCorner::BottomRight:
    {
        const Particle *p = particleHandler.getParticles().get({topLeft.x + size.x, topLeft.y + size.y});
        if (!p || (p->isSolid() && !p->isMoving()))
        {
            collided = true;
        }
    }
    break;
    }

    return collided;
}
