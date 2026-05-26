#include "world_generator.hpp"

#include "world_generator/generate_result.hpp"
#include <memory>

void WorldGenerator::generate_place(Vec2i origin, Vec2i radius)
{
    Vec2i chunkOrigin = r_world.getParticleHandler().getParticles().getChunkIndex(origin);
    Vec2u chunkSize   = r_world.getParticleHandler().getParticles().getChunkSize();

    for (int cy = chunkOrigin.y - radius.y; cy <= chunkOrigin.y + radius.y; ++cy)
    {
        for (int cx = chunkOrigin.x - radius.x; cx <= chunkOrigin.x + radius.x; ++cx)
        {
            Vec2i index = {cx, cy};
            if (m_generatedChunkMarkers.find(index) != m_generatedChunkMarkers.end())
            {
                continue;
            }

            m_generatedChunkMarkers.insert(index);

            for (unsigned int y = 0; y < chunkSize.y; ++y)
            {
                for (unsigned int x = 0; x < chunkSize.x; ++x)
                {
                    Vec2i pos = Vec2i(cx, cy) * chunkSize.toInt() + Vec2i(x, y);
                    generate_place_at_pos(pos);
                }
            }
        }
    }
}

void WorldGenerator::generate_place_at_pos(Vec2i pos)
{
    GenerateResult result;
    BiomeID biomeID = get_biome(pos);

    // switch (biomeID)
    // {
    // case BiomeID::Void:
    //     break;
    // case BiomeID::DesertLayer1:
    //     result = generate_desert_layer1(pos);
    //     break;
    // case BiomeID::DesertLayer2:
    //     result = generate_desert_layer2(pos);
    //     break;
    // }

    if (const GenerateResult *r = m_structureLayer.get(pos))
    {
        result = *r;
    }

    // for (auto &entity : result.entities)
    // {
    //     r_world.getEntityHandler().addEntity(std::move(entity));
    // }

    r_world.getParticleHandler().getEditor().set(pos, result.particle);
    r_world.getParticleHandler().getBackground().set(pos, result.backgroundColor);
    r_world.getParticleHandler().getBiomeMarkers().set(pos, biomeID);
}
