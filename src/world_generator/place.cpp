#include "world_generator.hpp"

#include "world_generator/spawn_data.hpp"
#include <optional>

void WorldGenerator::generate_place(Vec2i origin, Vec2i radius)
{
    Vec2i chunkOrigin = r_world.getParticleHandler().getParticles().getChunkIndex(origin);
    Vec2u chunkSize   = r_world.getParticleHandler().getParticles().getChunkSize();

    for (int cy = chunkOrigin.y - radius.y; cy <= chunkOrigin.y + radius.y; ++cy)
    {
        for (int cx = chunkOrigin.x - radius.x; cx <= chunkOrigin.x + radius.x; ++cx)
        {
            Vec2i chunkPos = {cx, cy};
            if (m_generatedChunkMarkers.find(chunkPos) != m_generatedChunkMarkers.end())
            {
                continue;
            }

            m_generatedChunkMarkers.insert(chunkPos);

            for (unsigned int y = 0; y < chunkSize.y; ++y)
            {
                for (unsigned int x = 0; x < chunkSize.x; ++x)
                {
                    Vec2i pos = chunkPos * chunkSize.toInt() + Vec2i(x, y);
                    generate_place_at_pos(pos);
                }
            }

            m_structureLayer.erase(chunkPos);
        }
    }
}

void WorldGenerator::generate_place_at_pos(Vec2i pos)
{
    PositionalSpawnData data;
    BiomeID biomeID = get_biome(pos);

    const std::optional<PositionalSpawnData> *structureData = m_structureLayer.get(pos);
    if (structureData && structureData->has_value())
    {
        data = structureData->value();
    }
    else
    {
        switch (biomeID)
        {
        case BiomeID::Void:
            break;
        case BiomeID::DesertLayer1:
            data = generate_desert_layer1(pos);
            break;
        case BiomeID::DesertLayer2:
            data = generate_desert_layer2(pos);
            break;
        }
    }

    if (data.entities)
    {
        for (auto &entity : data.entities(pos, r_assets))
        {
            r_world.getEntityHandler().addEntity(std::move(entity));
        }
    }

    r_world.getParticleHandler().getEditor().set(pos, data.particle);
    r_world.getParticleHandler().getEditor().setBackground(pos, data.backgroundColor);
    r_world.getParticleHandler().getEditor().setBiome(pos, biomeID);
}
