#include "scene_main.hpp"

#include "../logger/logger.hpp"

void MainScene::handle_world()
{
    int width = m_world_partitons[0]->getSize().x;
    int height = m_world_partitons[0]->getSize().y;

    Vec2<float> player_position = m_player.getPosition();

    int player_mod = ((int)player_position.y + height / 2) % (height);
    bool player_in_change_zone = (player_mod < 10) && (player_position.y > height / 2);

    if (!player_in_change_zone)
    {
        return;
    }

    int level = m_player.getPosition().y / (m_world_partitons[0]->getSize().y);
    if (level <= max_level)
    {
        return;
    }

    if (level % 2 == 1)
    {
        delete_world(m_world_partitons[0]);
        m_world_partitons[0] = new World(window.getSDLRenderer(), width, height);
        m_world_partitons[0]->setPosition(0, m_world_partitons[0]->getSize().y * (level + 1));

        World::Portal portal1{m_world_partitons[1], true, false, false, false};
        World::Portal portal2{m_world_partitons[0], false, true, false, false};

        m_world_partitons[0]->setPortal(portal1);
        m_world_partitons[1]->setPortal(portal2);
    }
    else
    {
        delete_world(m_world_partitons[1]);
        m_world_partitons[1] = new World(window.getSDLRenderer(), width, height);
        m_world_partitons[1]->setPosition(0, m_world_partitons[1]->getSize().y * (level + 1));

        World::Portal portal1{m_world_partitons[1], false, true, false, false};
        World::Portal portal2{m_world_partitons[0], true, false, false, false};

        m_world_partitons[0]->setPortal(portal1);
        m_world_partitons[1]->setPortal(portal2);
    }

    max_level = level;

    Log::log(Log::Type::Info, "MainScene", "User level index: " + std::to_string(level));
}