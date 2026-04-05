#pragma once

#include "math/random.hpp"
#include "utils/data.hpp"
#include "utils/data_structures/index_2d.hpp"
#include "world/generator/biomes/desert.hpp"
#include "world/particle_world/particle_world.hpp"

class Generator
{
  public:
    Generator(ParticleWorld &world) : r_world(world)
    {
        m_seed = Math::Random::weakRandInt(0, 10000);
    }

    void generateInRadius(Vec2i origin, Vec2i size)
    {
        Index2D chunkOrigin = r_world.getParticles().getChunkIndex(origin);
        Vec2i halfSize = size / 2;
        Vec2u chunkSize = r_world.getParticles().getChunkSize();

        for (int cy = chunkOrigin.y - halfSize.y;
             cy <= chunkOrigin.y + halfSize.y; ++cy)
        {
            for (int cx = chunkOrigin.x - halfSize.x;
                 cx <= chunkOrigin.x + halfSize.x; ++cx)
            {
                if (Utils::Data::doesVectorContain(m_generatedMarkers,
                                                   Index2D(cx, cy)))
                {
                    continue;
                }

                m_generatedMarkers.push_back(Index2D(cx, cy));

                for (unsigned int y = 0; y < chunkSize.y; ++y)
                {
                    for (unsigned int x = 0; x < chunkSize.x; ++x)
                    {
                        int ax = cx * chunkSize.x + x;
                        int ay = cy * chunkSize.y + y;

                        Particle p = generate_desert({ax, ay}, m_seed);
                        r_world.getEditor().set({ax, ay}, p);
                    }
                }
            }
        }
    }

  private:
    ParticleWorld &r_world;
    std::vector<Index2D> m_generatedMarkers;

    uint64_t m_seed = 0;
};
