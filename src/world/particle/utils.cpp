#include "particle_handler.hpp"

void ParticleHandler::set(int x, int y, Particle p)
{
    p.getVerlet().setPosition(x, y);
    m_particles.set(x, y, p);
}

void ParticleHandler::draw(int x, int y, Particle p, int radius)
{
    for (int ry = -radius; ry <= radius; ++ry)
    {
        for (int rx = -radius; rx <= radius; ++rx)
        {
            if (rx * rx + ry * ry <= radius * radius)
            {
                set(x + rx, y + ry, p);
            }
        }
    }
}
