#include "world_manager.hpp"

#include "../world_generator/world_generator.hpp"

WorldManager::WorldManager(Window &window, int width, int height) : m_window(window)
{
    m_world_size.x = width;
    m_world_size.x = height;

    WorldGenerator::Settings settings;
    settings.width = width;
    settings.height = height;
    settings.seed = 0;
    settings.preset = WorldGenerator::Settings::Preset::Test;

    m_worlds.push_back(WorldGenerator::generate(window.getSDLRenderer(), settings));
    m_worlds.push_back(WorldGenerator::generate(window.getSDLRenderer(), settings));

    m_worlds[1]->move(0, height);

    World::Portal portal1{m_worlds[1], false, true, false, false};
    World::Portal portal2{m_worlds[0], true, false, false, false};

    m_worlds[0]->setPortal(portal1);
    m_worlds[1]->setPortal(portal2);
}

WorldManager::~WorldManager()
{
    for (World *world : m_worlds)
    {
        if (world != nullptr)
        {
            delete world;
        }
    }
}