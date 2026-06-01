#include "test_long.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"
#include "world_generator/spawn_data.hpp"
#include <memory>

TestLongRoom::TestLongRoom()
{
    InitConfig config;
    config.colorPath  = "assets/rooms/test_long/test_long_color.png";
    config.lookupPath = "assets/rooms/test_long/test_long_lookup.png";
    init(config);

    m_data.get({92, 43})->entities = [&](Vec2i pos, const Assets &assets)
    {
        std::vector<std::unique_ptr<Entity>> out;
        auto entity = std::make_unique<Wuskkogel>(assets);
        entity->getBody().setPosition(pos);
        out.push_back(std::move(entity));
        return out;
    };
    m_data.get({337, 55})->entities = [&](Vec2i pos, const Assets &assets)
    {
        std::vector<std::unique_ptr<Entity>> out;
        auto entity = std::make_unique<Wuskkogel>(assets);
        entity->getBody().setPosition(pos);
        out.push_back(std::move(entity));
        return out;
    };
    m_data.get({337, 55})->entities = [&](Vec2i pos, const Assets &assets)
    {
        std::vector<std::unique_ptr<Entity>> out;
        auto entity = std::make_unique<Wuskkogel>(assets);
        entity->getBody().setPosition(pos);
        out.push_back(std::move(entity));
        return out;
    };
    m_data.get({540, 31})->entities = [&](Vec2i pos, const Assets &assets)
    {
        std::vector<std::unique_ptr<Entity>> out;
        auto entity = std::make_unique<Wuskkogel>(assets);
        entity->getBody().setPosition(pos);
        out.push_back(std::move(entity));
        return out;
    };
}

void TestLongRoom::writeToLayer(Vec2i worldTopLeft, ChunkMap<StructurePositionalSpawnData> &dataOut) const
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
