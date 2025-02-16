#include "world_manager.hpp"

#include "../engine/logger/logger.hpp"
#include "../world_generator/debug/wg_debug.hpp"

void WorldManager::update(Vec2<float> player_position)
{
    int width = m_worlds[0]->getSize().x;
    int height = m_worlds[0]->getSize().y;

    int player_mod = ((int)player_position.y + height / 2) % height;
    bool player_in_change_zone = (player_mod < 20) && (player_position.y > height / 2);

    if (!player_in_change_zone)
    {
        return;
    }

    int level = player_position.y / (m_worlds[0]->getSize().y);
    if (level <= max_level)
    {
        return;
    }

    bool next_level = level % 2 == 1;

    if (next_level)
    {
        delete_world(m_worlds[0]);
        m_worlds[0] = DebugWorldGenerator(m_window.getSDLRenderer(), WorldGenerator::Settings{width, height, 0}).world();
        m_worlds[0]->setPosition(0, m_worlds[0]->getSize().y * (level + 1));

        World::Portal portal1{m_worlds[1], true, false, false, false};
        World::Portal portal2{m_worlds[0], false, true, false, false};

        m_worlds[0]->setPortal(portal1);
        m_worlds[1]->setPortal(portal2);
    }
    else
    {
        delete_world(m_worlds[1]);
        m_worlds[1] = DebugWorldGenerator(m_window.getSDLRenderer(), WorldGenerator::Settings{width, height, 0}).world();
        m_worlds[1]->setPosition(0, m_worlds[1]->getSize().y * (level + 1));

        World::Portal portal1{m_worlds[1], false, true, false, false};
        World::Portal portal2{m_worlds[0], true, false, false, false};

        m_worlds[0]->setPortal(portal1);
        m_worlds[1]->setPortal(portal2);
    }

    max_level = level;

    Log::log(Log::Type::Info, "MainScene", "User level index: " + std::to_string(level));
}