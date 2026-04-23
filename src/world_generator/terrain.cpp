#include "desert/terrain.hpp"
#include "math/numbers.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/voronoi.hpp"
#include "utils/data.hpp"
#include "world_generator.hpp"

void WorldGenerator::generate_terrain(Vec2i origin)
{
    Index2D chunkOrigin =
        r_world.getParticleHandler().getParticles().getChunkIndex(origin);
    Vec2u chunkSize =
        r_world.getParticleHandler().getParticles().getChunkSize();

    for (int cy = chunkOrigin.y - m_generateRadius.y;
         cy <= chunkOrigin.y + m_generateRadius.y; ++cy)
    {
        for (int cx = chunkOrigin.x - m_generateRadius.x;
             cx <= chunkOrigin.x + m_generateRadius.x; ++cx)
        {
            Index2D index(cx, cy);
            if (Utils::Data::doesVectorContain(m_generatedChunkMarkers, index))
            {
                continue;
            }

            m_generatedChunkMarkers.push_back(index);

            for (unsigned int y = 0; y < chunkSize.y; ++y)
            {
                for (unsigned int x = 0; x < chunkSize.x; ++x)
                {
                    int ax = cx * chunkSize.x + x;
                    int ay = cy * chunkSize.y + y;

                    generate_terrain_at_pos({ax, ay});
                }
            }
        }
    }
}

void WorldGenerator::generate_terrain_at_pos(Vec2i pos)
{
    float biomeEdgeWarble =
        Math::Perlin::sampleEx(pos.toFloat(), {200, 200}, 5, m_seed) - 0.5f;

    Math::Voronoi::Sample sample =
        Math::Voronoi::sampleEx(pos.toFloat() + biomeEdgeWarble * 100.0f,
                                m_biomeSize.toFloat(), m_seed);

    std::vector<BiomeID> biomes;

    float biomeTransitioner1 =
        Math::Perlin::sampleEx(pos.toFloat(), {200, 200}, 5, m_seed);

    if (Math::Numbers::between(pos.y, 0 + (int)(biomeTransitioner1 * 20),
                               800 + (int)(biomeTransitioner1 * 100)))
    {
        biomes.push_back(BiomeID::DesertLayer1);
    }
    if (Math::Numbers::between(pos.y, 800 - (int)(biomeTransitioner1 * 100),
                               1000000))
    {
        biomes.push_back(BiomeID::DesertLayer2);
    }

    size_t size = biomes.size();
    if (size <= 0)
    {
        return;
    }

    unsigned int selector =
        Math::Random::hashFromPosition(sample.cell, m_seed) % biomes.size();

    BiomeID id = biomes[selector];

    Particle p;
    switch (id)
    {
    case BiomeID::DesertLayer1:
        p = generate_desert_layer1(pos, m_seed);
        break;
    case BiomeID::DesertLayer2:
        p = generate_desert_layer2(pos, m_seed);
        break;
    default:
        break;
    }

    r_world.getParticleHandler().getBiomeMarkers().set(pos, id);
    r_world.getParticleHandler().getEditor().set(pos, p);
}
