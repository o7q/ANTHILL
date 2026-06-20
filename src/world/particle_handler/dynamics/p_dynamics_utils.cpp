#include "p_dynamics_handler.hpp"

#include "px/basic_types/rectangle.hpp"

bool PDynamicsHandler::can_solid_occupy(const Particle *p)
{
    if (!p)
    {
        return false;
    }
    return p->isGas() || p->isLiquid();
}

bool PDynamicsHandler::can_liquid_occupy(const Particle *p)
{
    if (!p)
    {
        return false;
    }
    return p->isGas();
}

bool PDynamicsHandler::can_gas_occupy(const Particle *p)
{
    if (!p)
    {
        return false;
    }
    return p->isAir();
}

void PDynamicsHandler::applyForce(px::Vec2i origin, int radius, float power)
{
    px::Rectangle_i rect(origin, {radius * 2, radius * 2});
    px::Vec2i a = rect.getA();
    px::Vec2i b = rect.getB();

    for (int y = a.y; y < b.y; ++y)
    {
        for (int x = a.x; x < b.x; ++x)
        {
            Particle *p = r_particles.get({x, y});

            if (!p || p->getPhysicsType() == Particle::PhysicsType::None)
            {
                continue;
            }

            px::Vec2f dir = origin.toFloat() - p->getVerlet().getPosition();

            if (dir.length() < 0.001f)
            {
                continue;
            }

            px::Vec2f normal = dir.normalize();
            px::Vec2f vel    = normal * power;

            p->getVerlet().setForce(vel);
        }
    }
}
