#include "p_dynamics_handler.hpp"

void PDynamicsHandler::applyForce(float x, float y, float power, float dt)
{
    for (auto &[chunkPos, chunk] : r_particles.getChunks())
    {
        Vec2<unsigned int> chunkSize = r_particles.getChunkSize();
        for (unsigned int cy = 0; cy < chunkSize.y; ++cy)
        {
            for (unsigned int cx = 0; cx < chunkSize.x; ++cx)
            {
                const int px = chunkPos.x * chunkSize.x + cx;
                const int py = chunkPos.y * chunkSize.y + cy;
                Particle *p = r_particles.get(px, py);

                if (!p)
                {
                    continue;
                }

                if (p->isAir())
                {
                    continue;
                }

                Vec2<float> dir =
                    p->getVerlet().getPosition() - Vec2<float>(x, y);

                float distance = dir.length();

                if (distance > 0.001f)
                {
                    dir = dir / distance;
                }

                float strength = power;
                Vec2<float> force = dir * strength;

                p->getVerlet().setVelocity(force.x, force.y, dt);
            }
        }
    }
}