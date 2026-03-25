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

void ParticleHandler::textureToParticles(const Texture &texture, Vec2i pos,
                                         Particle particleBase)
{
    Vec2i size = texture.getSize().toInt();
    Vec2i halfSize = texture.getSize().toInt() / 2;

    for (int y = 0; y < size.y; ++y)
    {
        for (int x = 0; x < size.x; ++x)
        {
            Color col = texture.getPixel(x, y);
            particleBase.setColor(col);

            set(pos.x + static_cast<int>(x) - halfSize.x,
                pos.y + static_cast<int>(y) - halfSize.y, particleBase);
        }
    }
}
