#include "world_manager.hpp"

void WorldManager::purge()
{
    for (World *world : m_worlds)
    {
        if (world != nullptr)
        {
            delete world;
        }
    }

    m_worlds.clear();

    index = 0;
    vertical_pos_index = 0;
}

void WorldManager::purge_first_world()
{
    if (m_worlds.empty())
    {
        return;
    }

    if (m_worlds[0] != nullptr)
    {
        delete m_worlds[0];
    }

    m_worlds.erase(m_worlds.begin());

    if (m_worlds.empty())
    {
        return;
    }

    WorldPhysics::Portal portal = m_worlds[0]->getWorldPhysics()->getPortal();
    portal.up = nullptr;
    m_worlds[0]->getWorldPhysics()->setPortal(portal);
}