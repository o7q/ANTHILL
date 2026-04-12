#include "world/generator/desert/terrain.hpp"
#include "generator.hpp"
#include "math/random.hpp"
#include "math/voronoi.hpp"
#include "utils/data.hpp"
#include "world/generator/biome.hpp"

void Generator::generate_terrain(Vec2i origin)
{
    Index2D chunkOrigin = r_world.getParticles().getChunkIndex(origin);
    Vec2u chunkSize = r_world.getParticles().getChunkSize();

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

void Generator::generate_terrain_at_pos(Vec2i pos)
{
    float pd =
        Math::Perlin::sampleEx(pos.toFloat(), {20, 20}, 1, m_seed) - 0.5f;

    pd *= pos.y / 100.0f;

    Math::Voronoi::Sample sample = Math::Voronoi::sampleEx(
        pos.toFloat() + pd * 20, m_biomeSize.toFloat(), m_seed);

    unsigned int maxLayer = (pos.y > ((pd + 0.5f) * 20 + 5000) ? 2 : 1);

    unsigned int biomeSelector =
        Math::Random::hashFromPosition(sample.cell) % maxLayer;

    BiomeID biomeID = BiomeID::Surface;
    if (pos.y > (pd + 0.5f) * 50.0f)
    {
        switch (biomeSelector)
        {
        case 0:
            biomeID = BiomeID::Desert;
            break;
        case 1:
            biomeID = BiomeID::Hell;
            break;
        }
    }

    Particle p;

    switch (biomeID)
    {
    case BiomeID::Surface:
        p = Particle();
        break;
    case BiomeID::Desert:
        p = generate_desert_terrain(pos, m_seed);
        break;
    case BiomeID::Hell:
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::None);
        p.setColor(Color(255, 0, 0));
        break;
    }

    r_world.getEditor().set(pos, p);
}
