#include "world_manager.hpp"

#include "../world_generator/debug/wg_debug.hpp"

WorldManager::WorldManager(Window &window, int width, int height) : m_window(window)
{
    m_world_size.x = width;
    m_world_size.x = height;

    m_worlds.push_back(DebugWorldGenerator(window.getSDLRenderer(), WorldGenerator::Settings{width, height, -1}).world());
    m_worlds.push_back(DebugWorldGenerator(window.getSDLRenderer(), WorldGenerator::Settings{width, height, -1}).world());

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