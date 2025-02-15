#include "wp_manager.hpp"

void WPManager::delete_world(World *world)
{
    if (world != nullptr)
    {
        delete world;
        world = nullptr;
    }
}