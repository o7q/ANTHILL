#include "sand_room.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"

SandRoom::SandRoom()
{
    InitConfig config;
    config.backgroundPath     = "assets/rooms/sand/sand_background.png";
    config.particleColorPath  = "assets/rooms/sand/sand_color.png";
    config.particleLookupPath = "assets/rooms/sand/sand_lookup.png";
    init(config);

    if (getSize().x == 0 || getSize().y == 0)
    {
        return;
    }

    m_data.at({125, 295}).entities = [](Vec2i pos, const Assets &assets)
    {
        std::vector<std::unique_ptr<Entity>> entities;
        auto wuskkogel = std::make_unique<Wuskkogel>(assets);
        wuskkogel->getBody().setPosition(pos);
        entities.push_back(std::move(wuskkogel));
        return entities;
    };
}
