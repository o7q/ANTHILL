#include "world_manager.hpp"

#include "../engine/math/vector.hpp"
#include "../engine/logger/logger.hpp"

void WorldManager::generateLatest()
{
    if (m_world_queue.empty())
    {
        return;
    }

    World *world_new = WorldGenerator::generate(m_window.getSDLRenderer(), m_world_queue[0]);
    m_world_queue.erase(m_world_queue.begin());

    world_new->setPosition(0, vertical_pos_index);
    vertical_pos_index += world_new->getSize().y;

    if (index > 0)
    {
        World *world_above = m_worlds[index - 1];

        WorldPhysics::Portal portal_above = world_above->getWorldPhysics()->getPortal();
        portal_above.down = world_new->getWorldPhysics();
        world_above->getWorldPhysics()->setPortal(portal_above);

        WorldPhysics::Portal portal;
        portal.up = world_above->getWorldPhysics();
        world_new->getWorldPhysics()->setPortal(portal);
    }

    m_worlds.push_back(world_new);

    float size_in_memory = size_in_memory_mb();
    if (size_in_memory >= m_max_memory_mb)
    {
        purge_first_world();
        Log::log(Log::Level::Info, "WorldManager", "Purging world: 0 - Memory over limit: (" + std::to_string(size_in_memory) + '/' + std::to_string(m_max_memory_mb) + " MB)");
    }
    else
    {
        ++index;
    }
}

void WorldManager::queue(WorldGenerator::Settings settings)
{
    m_world_queue.push_back(settings);
}