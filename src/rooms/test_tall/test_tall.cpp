#include "test_tall.hpp"
#include "world_generator/spawn_data.hpp"

TestTallRoom::TestTallRoom()
{
    InitConfig config;
    config.colorPath  = "assets/rooms/test_tall/test_tall_color.png";
    config.lookupPath = "assets/rooms/test_tall/test_tall_lookup.png";
    init(config);
}

void TestTallRoom::writeToLayer(px::Vec2i worldTopLeft,
                                px::ChunkMap<StructurePositionalSpawnData> &dataOut) const
{
    for (int y = 0; y < getSize().y; ++y)
    {
        for (int x = 0; x < getSize().x; ++x)
        {
            px::Vec2i localPos = {x, y};

            if (const StructurePositionalSpawnData *data = m_data.get(localPos))
            {
                dataOut.set(worldTopLeft + localPos, *data);
            }
        }
    }
}
