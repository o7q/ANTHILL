#include "core/math/random.hpp"
#include "world_generator.hpp"

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/circle.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/segment.hpp"
#include "core/math/geometry/triangle.hpp"
#include "core/math/graph.hpp"
#include "core/math/line.hpp"
#include "core/math/mesh.hpp"
#include "level_generator/layout_generator.hpp"
#include "world/particle_handler/particle_lookup.hpp"
#include "world_generator/spawn_data.hpp"
#include <unordered_set>
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
        NodeGraph<const Room *> masterLayout;

        masterLayout.set({0, 0}, {&r_assets.rooms().get(RoomID::TestSquare)});

        {
            LevelLayoutGenerator::Config config;
            config.bounds                    = {{0, 1500}, {3000, 3000}};
            config.initialRoomPlacementCount = 1000;
            config.roomPool.push_back({&r_assets.rooms().get(RoomID::TestSquare), 1});
            config.roomPool.push_back({&r_assets.rooms().get(RoomID::TestSquareBig), 1});
            config.roomPool.push_back({&r_assets.rooms().get(RoomID::TestTall), 1});
            config.roomPool.push_back({&r_assets.rooms().get(RoomID::TestLong), 1});
            config.roomSpread     = {500, 500};
            config.roomMinSpacing = {5, 5};

            LevelLayoutGenerator generator;
            generator.setConfig(config);
            masterLayout.merge(generator.generate(m_seed));
        }

        for (auto &[index, node] : masterLayout.getNodes())
        {
            Rectangle_i dummyRect(index, node.value->getSize());
            node.value->writeToLayer(dummyRect.getA(), m_structureLayer);
        }

        std::vector<Triangle_i> triangulation =
            Math::Mesh::generateTriangulation(masterLayout.generatePositions());

        masterLayout = Math::Graph::connectNodesFromTriangulation(triangulation, masterLayout);
        masterLayout = Math::Graph::minimumSpanningTree(masterLayout);

        std::unordered_set<Segment_i, SegmentHash<int>> connections = masterLayout.generateConnections();

        for (Segment_i s : connections)
        {
            Math::Line::bresenhamLine(s.a, s.b,
                                      [&](Vec2i pos)
                                      {
                                          Circle_i circ{pos, 15};

                                          circ.rasterize(
                                              [&](Vec2i pos2)
                                              {
                                                  StructurePositionalSpawnData dat;
                                                  dat.overwriteTerrainParticle = true;
                                                  dat.particle                 = Particle();
                                                  m_structureLayer.set(pos2, dat);
                                              });
                                          return false;
                                      });
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
    // BiomeID biomeID = get_biome(pos);
    // switch (biomeID)
    // {
    // case BiomeID::Void:
    //     break;
    // case BiomeID::DesertLayer1:
    //     biomeData = generate_desert_layer1(pos);
    //     break;
    // case BiomeID::DesertLayer2:
    //     biomeData = generate_desert_layer2(pos);
    //     break;
    // }
    if (pos.y > 0)
    {
        Particle stone = createParticlePreset(ParticlePresetID::Stone).value();
        float rand     = Math::Random::seededRandomInt(90, 100, m_seed + pos.x * pos.y) / 100.0f;
        stone.setColor(Color(100 * rand, 100 * rand, 100 * rand));
        biomeData.particle = stone;
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
    // r_world.getParticleHandler().getEditor().setBiome(pos, biomeID);
}
