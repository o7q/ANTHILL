#include "p_dynamics_handler.hpp"

bool PDynamicsHandler::can_solid_occupy(Particle *p)
{
    if (!p)
    {
        return true;
    }
    return p->isGas() || p->isLiquid();
}

bool PDynamicsHandler::can_liquid_occupy(Particle *p)
{
    if (!p)
    {
        return true;
    }
    return p->isGas();
}

bool PDynamicsHandler::can_gas_occupy(Particle *p)
{
    if (!p)
    {
        return true;
    }
    return p->isAir();
}

void PDynamicsHandler::applyForce(int x, int y, float power, float dt)
{
    for (auto &[chunkPos, chunk] : r_particles.getChunks())
    {
        Vec2u chunkSize = r_particles.getChunkSize();
        for (unsigned int cy = 0; cy < chunkSize.y; ++cy)
        {
            for (unsigned int cx = 0; cx < chunkSize.x; ++cx)
            {
                const int px = chunkPos.x * chunkSize.x + cx;
                const int py = chunkPos.y * chunkSize.y + cy;
                Particle *p = r_particles.get({px, py});

                if (!p)
                {
                    continue;
                }

                if (p->isAir() || p->isImmovable())
                {
                    continue;
                }

                Vec2f dir = p->getVerlet().getPosition() - Vec2f(x, y);

                float distance = dir.length();

                if (distance > 0.001f)
                {
                    dir = dir / distance;
                }

                float strength = power;
                Vec2f force = dir * strength;

                p->getVerlet().setVelocity(force, dt);
            }
        }
    }
}
