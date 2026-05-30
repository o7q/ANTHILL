#pragma once

#include "core/data_structures/chunk_map.hpp"
#include "core/math/random.hpp"
#include "core/texture/texture.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/particle.hpp"

class ParticleEditor
{
  public:
    ParticleEditor(ChunkMap<Particle> &particles, ChunkMap<BiomeID> &biomeMarkers,
                   ChunkMap<Color> &background)
        : r_particles(particles), r_biomeMarkers(biomeMarkers), r_background(background)
    {
    }

    void set(Vec2i pos, Particle p, bool force = false)
    {
        const Particle *existing = r_particles.get(pos);
        if (existing)
        {
            int hardness = existing->getHardness();
            bool canSet  = true;

            if (hardness != 0 && !force)
            {
                if (hardness <= -1 || Math::Random::unseededRandomInt(0, hardness + 1) != 0)
                {
                    canSet = false;
                }
            }

            if (!canSet)
            {
                return;
            }
        }

        p.getVerlet().setPosition(pos.toFloat());
        r_particles.set(pos, p);
    }

    void setRadius(Vec2i pos, Particle p, int radius = 5)
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

    void setBackground(Vec2i pos, Color color) { r_background.set(pos, color); }
    void setBiome(Vec2i pos, BiomeID biome) { r_biomeMarkers.set(pos, biome); }

    void textureToParticles(const Texture &texture, Vec2i pos, Particle particleBase)
    {
        Vec2i size     = texture.getSize().toInt();
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
    ChunkMap<BiomeID> &r_biomeMarkers;
    ChunkMap<Color> &r_background;
};
