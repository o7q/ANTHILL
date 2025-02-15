#include "wp_manager.hpp"

WPManager::WPManager(Window &window, int partiton_width, int partiton_height) : m_window(window)
{
    m_partition_size.x = partiton_width;
    m_partition_size.x = partiton_height;

    m_world_partitons.push_back(new World(window.getSDLRenderer(), partiton_width, partiton_height));
    m_world_partitons.push_back(new World(window.getSDLRenderer(), partiton_width, partiton_height));

    m_world_partitons[1]->move(0, partiton_height);

    World::Portal portal1{m_world_partitons[1], false, true, false, false};
    World::Portal portal2{m_world_partitons[0], true, false, false, false};

    m_world_partitons[0]->setPortal(portal1);
    m_world_partitons[1]->setPortal(portal2);
}

WPManager::~WPManager()
{
    for (World *world_partition : m_world_partitons)
    {
        if (world_partition != nullptr)
        {
            delete world_partition;
        }
    }
}