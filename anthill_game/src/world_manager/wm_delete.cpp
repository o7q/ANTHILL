#include "world_manager.hpp"

void WorldManager::delete_world(World *world)
{
    if (world != nullptr)
    {
        delete world;
        world = nullptr;
    }
}