#include "world_generator.hpp"

#include "biomes/desert.hpp"
#include "core/utils/data.hpp"
#include "world_generator/generate_result.hpp"

void WorldGenerator::place_terrain(Vec2i origin, Vec2i radius)
{
    Index2D chunkOrigin = r_world.getParticleHandler().getParticles().getChunkIndex(origin);
    Vec2u chunkSize     = r_world.getParticleHandler().getParticles().getChunkSize();

    for (int cy = chunkOrigin.y - radius.y; cy <= chunkOrigin.y + radius.y; ++cy)
    {
        for (int cx = chunkOrigin.x - radius.x; cx <= chunkOrigin.x + radius.x; ++cx)
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
                    int ax    = cx * chunkSize.x + x;
                    int ay    = cy * chunkSize.y + y;
                    Vec2i pos = {ax, ay};

                    BiomeID biomeID = get_biome({ax, ay});

                    GenerateResult result;
                    switch (biomeID)
                    {
                    case BiomeID::Void:
                        break;
                    case BiomeID::DesertLayer1:
                        result = generate_desert_layer1(pos, m_seed, r_assets);
                        break;
                    case BiomeID::DesertLayer2:
                        result = generate_desert_layer2(pos, m_seed, r_assets);
                        break;
                    }

                    r_world.getParticleHandler().getEditor().set(pos, result.particle);

                    if (result.spawnEntity)
                    {
                        r_world.getEntityHandler().addEntity(std::move(result.spawnEntity));
                    }

                    r_world.getParticleHandler().getBiomeMarkers().set(pos, biomeID);
                }
            }
        }
    }
}
