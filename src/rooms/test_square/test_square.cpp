#include "test_square.hpp"
#include "world_generator/spawn_data.hpp"

TestSquareRoom::TestSquareRoom()
{
    InitConfig config;
    config.colorPath  = "assets/rooms/test_square/test_square_color.png";
    config.lookupPath = "assets/rooms/test_square/test_square_lookup.png";
    init(config);
}

void TestSquareRoom::writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const
{
    for (int y = 0; y < getSize().y; ++y)
    {
        for (int x = 0; x < getSize().x; ++x)
        {
            Vec2i localPos = {x, y};

            if (const StructurePositionalSpawnData *data = m_data.get(localPos))
            {
                dataOut.set(worldTopLeft + localPos, *data);
            }
        }
    }
}
