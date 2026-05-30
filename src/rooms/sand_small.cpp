#include "sand_small.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"
#include "world_generator/spawn_data.hpp"

SandSmallRoom::SandSmallRoom()
{
    InitConfig config;
    config.colorPath      = "assets/rooms/sand_small/sand_small_color.png";
    config.lookupPath     = "assets/rooms/sand_small/sand_small_lookup.png";
    config.backgroundPath = "assets/rooms/sand_small/sand_small_background.png";
    init(config);

    m_data.get(Vec2i(56, 62))->entities = [](Vec2i pos, const Assets &assets)
    {
        std::vector<std::unique_ptr<Entity>> entities;
        auto wuskkogel = std::make_unique<Wuskkogel>(assets);
        wuskkogel->getBody().setPosition(pos);
        entities.push_back(std::move(wuskkogel));
        return entities;
    };
}

void SandSmallRoom::writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const
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
