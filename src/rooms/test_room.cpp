#include "test_room.hpp"
#include "entities/player_point/player_point.hpp"

TestRoom::TestRoom()
{
    InitConfig config;
    config.backgroundPath     = "assets/rooms/test/test_background.png";
    config.particleColorPath  = "assets/rooms/test/test_color.png";
    config.particleLookupPath = "assets/rooms/test/test_lookup.png";
    init(config);

    m_data.at({125, 295}).entities = [](Vec2i pos, const Assets &assets)
    {
        std::vector<std::unique_ptr<Entity>> entities;
        auto wuskkogel = std::make_unique<PlayerPoint>(pos);
        wuskkogel->getBody().setPosition(pos);
        entities.push_back(std::move(wuskkogel));
        return entities;
    };
}
