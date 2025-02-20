#include "scene_main.hpp"

void MainScene::update_world()
{
    m_world_manager.updateQueue();

    for (World *world : m_world_manager.getWorlds())
    {
        world->update(&m_world_update_bb);
    }
}