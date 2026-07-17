#pragma once

#include "px/basic_types/circle.hpp"
#include "px/data_structures/chunk_map.hpp"
#include "px/texture/texture.hpp"
#include "px/utils/circles.hpp"
#include "px/utils/random.hpp"
#include "world/particle_handler/biome.hpp"
#include "world/particle_handler/particle.hpp"

class ParticleEditor
{
  public:
    ParticleEditor(px::ChunkMap<Particle> &particles, px::ChunkMap<BiomeID> &biomeMarkers,
                   px::ChunkMap<px::Color> &background)
        : r_particles(particles), r_biomeMarkers(biomeMarkers), r_background(background)
    {
    }

    void set(px::Vec2i pos, Particle p, bool force = false)
    {
        const Particle *existing = r_particles.get(pos);
        if (existing)
        {
            int hardness = existing->getHardness();
            bool canSet  = true;

            if (hardness != 0 && !force)
            {
                if (hardness <= -1 || px::Random::unseededRandomInt(0, hardness + 1) != 0)
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

    void setRadius(px::Vec2i position, Particle p, int radius = 5)
    {
        px::Circle_i circle{position, radius};
        px::Circles::fill(circle, [&](px::Vec2i pos) { set(pos, p); });
    }

    void setBackground(px::Vec2i pos, px::Color color) { r_background.set(pos, color); }
    void setBiome(px::Vec2i pos, BiomeID biome) { r_biomeMarkers.set(pos, biome); }

    void textureToParticles(const px::Texture &texture, px::Vec2i pos, Particle particleBase)
    {
        px::Vec2i size     = texture.getSize().toInt();
        px::Vec2i halfSize = texture.getSize().toInt() / 2;

        for (int y = 0; y < size.y; ++y)
        {
            for (int x = 0; x < size.x; ++x)
            {
                px::Color col = texture.getPixel(px::Vec2i{x, y}.toUnsignedInt());
                particleBase.setColor(col);

                set(pos + px::Vec2i{x, y} - halfSize, particleBase);
            }
        }
    }

  private:
    px::ChunkMap<Particle> &r_particles;
    px::ChunkMap<BiomeID> &r_biomeMarkers;
    px::ChunkMap<px::Color> &r_background;
};
