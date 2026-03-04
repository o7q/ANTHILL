#include "world_collision_handler.hpp"

#include "types/bounding_box.hpp"
#include "world/particle.hpp"

bool WorldCollisionHandler::againstSolidSurface(Vec2<int> pos,
                                                BoundingBox::Side side)
{
    Vec2<int> size = m_collisionBox.getSize();
    Vec2<int> topLeft = pos + m_collisionBox.getA();

    bool collided = false;

    auto query = [&](Particle *p)
    {
        if (p->isSolid() && !p->inMotion())
        {
            collided = true;
            return true;
        }
        return false;
    };

    switch (side)
    {
    case BoundingBox::Side::Top:
    {
        Vec2<int> start = Vec2<int>(topLeft.x, topLeft.y - 1);
        Vec2<int> end = Vec2<int>(topLeft.x + size.x - 1, topLeft.y - 1);
        r_world.getParticleHandler().query(start, end, query);
    }
    break;
    case BoundingBox::Side::Right:
    {
        Vec2<int> start = Vec2<int>(topLeft.x + size.x, topLeft.y);
        Vec2<int> end = Vec2<int>(topLeft.x + size.x, topLeft.y + size.y - 1);
        r_world.getParticleHandler().query(start, end, query);
    }
    break;
    case BoundingBox::Side::Bottom:
    {
        Vec2<int> start = Vec2<int>(topLeft.x, topLeft.y + size.y);
        Vec2<int> end = Vec2<int>(topLeft.x + size.x - 1, topLeft.y + size.y);
        r_world.getParticleHandler().query(start, end, query);
    }
    break;
    case BoundingBox::Side::Left:
    {
        Vec2<int> start = Vec2<int>(topLeft.x - 1, topLeft.y);
        Vec2<int> end = Vec2<int>(topLeft.x - 1, topLeft.y + size.y - 1);
        r_world.getParticleHandler().query(start, end, query);
    }
    break;
    }

    return collided;
}

bool WorldCollisionHandler::againstSolidCorner(Vec2<int> pos,
                                               BoundingBox::Corner corner)
{
    Vec2<int> size = m_collisionBox.getSize();
    Vec2<int> topLeft = pos + m_collisionBox.getA();

    bool collided = false;
    switch (corner)
    {
    case BoundingBox::Corner::TopLeft:
    {
        if (Particle *p = r_world.getParticleHandler().getParticles().get(
                topLeft.x + size.x, topLeft.y - 1))
        {
            if (p->isSolid() && !p->inMotion())
            {
                collided = true;
            }
        }
    }
    break;
    case BoundingBox::Corner::TopRight:
    {
        if (Particle *p = r_world.getParticleHandler().getParticles().get(
                topLeft.x - 1, topLeft.y - 1))
        {
            if (p->isSolid() && !p->inMotion())
            {
                collided = true;
            }
        }
    }
    break;
    case BoundingBox::Corner::BottomLeft:
    {
        if (Particle *p = r_world.getParticleHandler().getParticles().get(
                topLeft.x - 1, topLeft.y + size.y))
        {
            if (p->isSolid() && !p->inMotion())
            {
                collided = true;
            }
        }
    }
    break;
    case BoundingBox::Corner::BottomRight:
    {
        if (Particle *p = r_world.getParticleHandler().getParticles().get(
                topLeft.x + size.x, topLeft.y + size.y))
        {
            if (p->isSolid() && !p->inMotion())
            {
                collided = true;
            }
        }
    }
    break;
    }

    return collided;
}
