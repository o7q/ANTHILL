#include "world_generator.hpp"

#include "core/data_structures/node_graph.hpp"
#include "core/math/geometry/rectangle.hpp"
#include "core/math/random.hpp"
#include "level_generator/layout_generator.hpp"

WorldGenerator::WorldGenerator(World &world, const Assets &assets)
    : r_world(world), r_assets(assets), m_structureLayer({32, 32})
{
    m_seed = Math::Random::unseededRandomInt(0, 1000000);
}

void WorldGenerator::generate(Vec2i origin, Vec2i radius)
{
    if (!m_structureGenerated)
    {
        LevelLayoutGenerator::Config config;
        config.bounds                    = {{0, 1000}, {2000, 2000}};
        config.initialRoomPlacementCount = 100;
        config.roomPool.push_back({&r_assets.rooms().get(RoomID::Sand), 1});
        config.roomSpread     = {10, 10};
        config.roomMinSpacing = {0, 0};

        LevelLayoutGenerator generator;
        generator.setConfig(config);
        NodeGraph<const Room *> roomGraph = generator.generate(m_seed);

        for (auto &[index, node] : roomGraph.getNodes())
        {
            Rectangle_i roomRect(index, node.value->getSize());

            Vec2i a = roomRect.getA();

            for (int y = 0; y < node.value->getSize().y; ++y)
            {
                for (int x = 0; x < node.value->getSize().x; ++x)
                {
                    m_structureLayer.set(a + Vec2i(x, y), node.value->getData().at({x, y}));
                }
            }
        }
    }

    m_structureGenerated = true;
    generate_place(origin, radius);
}
