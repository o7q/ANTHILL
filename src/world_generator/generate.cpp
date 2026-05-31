#include "world_generator.hpp"

#include "core/math/geometry/triangle.hpp"
#include "core/math/graph.hpp"
#include "core/math/mesh.hpp"
#include "level_generator/layout_generator.hpp"
#include "world_generator/spawn_data.hpp"
#include <vector>

void WorldGenerator::generate(Vec2i origin, Vec2i radius)
{
    generate_prepare_structures();
    generate_set_in_world(origin, radius);
}

void WorldGenerator::generate_prepare_structures()
{
    if (!m_structureGenerated)
    {
        LevelLayoutGenerator::Config config;
        config.bounds                    = {{0, 2500}, {5000, 5000}};
        config.initialRoomPlacementCount = 1000;
        config.roomPool.push_back({&r_assets.rooms().get(RoomID::SandSmall), 1});
        config.roomSpread     = {500, 500};
        config.roomMinSpacing = {0, 0};

        LevelLayoutGenerator generator;
        generator.setConfig(config);
        NodeGraph<const Room *> roomGraph = generator.generate(m_seed);

        std::vector<Vec2i> positions;

        for (auto &[index, node] : roomGraph.getNodes())
        {
            positions.push_back(index);
        }

        std::vector<Triangle_i> triangulation = Math::Mesh::generateTriangulation(positions);
        roomGraph = Math::Graph::connectNodesFromTriangulation(triangulation, roomGraph);

        for (auto &[index, node] : roomGraph.getNodes())
        {
            Rectangle_i roomRect(index, node.value->getSize());
            Vec2i a = roomRect.getA();
            node.value->writeToLayer(a, m_structureLayer);
        }
    }

    m_structureGenerated = true;
}

void WorldGenerator::generate_set_in_world(Vec2i origin, Vec2i radius)
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
                    generate_set_in_world_at_pos(pos);
                }
            }

            m_structureLayer.erase(chunkPos);
        }
    }
}

void WorldGenerator::generate_set_in_world_at_pos(Vec2i pos)
{
    PositionalSpawnData biomeData;
    BiomeID biomeID = get_biome(pos);
    switch (biomeID)
    {
    case BiomeID::Void:
        break;
    case BiomeID::DesertLayer1:
        biomeData = generate_desert_layer1(pos);
        break;
    case BiomeID::DesertLayer2:
        biomeData = generate_desert_layer2(pos);
        break;
    }
    const StructurePositionalSpawnData *structureData = m_structureLayer.get(pos);

    PositionalSpawnData finalData;
    if (structureData)
    {
        finalData.particle =
            structureData->overwriteTerrainParticle ? structureData->particle : biomeData.particle;
        finalData.backgroundColor = structureData->overwriteTerrainBackground ? structureData->backgroundColor
                                                                              : biomeData.backgroundColor;
        finalData.entities =
            structureData->overwriteTerrainEntities ? structureData->entities : biomeData.entities;
    }
    else
    {
        finalData = biomeData;
    }

    if (finalData.entities)
    {
        for (auto &entity : finalData.entities(pos, r_assets))
        {
            r_world.getEntityHandler().addEntity(std::move(entity));
        }
    }

    r_world.getParticleHandler().getEditor().set(pos, finalData.particle);
    r_world.getParticleHandler().getEditor().setBackground(pos, finalData.backgroundColor);
    r_world.getParticleHandler().getEditor().setBiome(pos, biomeID);
}
