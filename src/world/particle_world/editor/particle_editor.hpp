#pragma once

#include "backend/texture/texture.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/particle_world/particle.hpp"

class ParticleEditor
{
  public:
    ParticleEditor(ChunkMap<Particle> &particles) : r_particles(particles) {}

    void set(Vec2i pos, Particle p)
    {
        p.getVerlet().setPosition(pos.toFloat());
        r_particles.set(pos, p);
    }

    void draw(Vec2i pos, Particle p, int radius = 5)
    {
        for (int ry = -radius; ry <= radius; ++ry)
        {
            for (int rx = -radius; rx <= radius; ++rx)
            {
                if (rx * rx + ry * ry <= radius * radius)
                {
                    set(pos + Vec2i(rx, ry), p);
                }
            }
        }
    }

    void textureToParticles(const Texture &texture, Vec2i pos,
                            Particle particleBase)
    {
        Vec2i size = texture.getSize().toInt();
        Vec2i halfSize = texture.getSize().toInt() / 2;

        for (int y = 0; y < size.y; ++y)
        {
            for (int x = 0; x < size.x; ++x)
            {
                Color col = texture.getPixel(Vec2u(x, y));
                particleBase.setColor(col);

                set(pos + Vec2i(x, y) - halfSize, particleBase);
            }
        }
    }

  private:
    ChunkMap<Particle> &r_particles;
};
