#include "world_manager.hpp"

float WorldManager::size_in_memory_mb()
{
    float approx_mem_size = 0;

    const int world_mem_size = sizeof(World);
    const int world_physics_mem_size = sizeof(WorldPhysics);
    const int particle_mem_size = sizeof(Particle);
    const int texture_mem_size = sizeof(Texture);

    for (World *world : m_worlds)
    {
        Vec2<int> world_size = world->getSize();
        approx_mem_size += world_mem_size;
        approx_mem_size += world_physics_mem_size;
        approx_mem_size += texture_mem_size;
        approx_mem_size += particle_mem_size * world_size.x * world_size.y;
    }

    return approx_mem_size / 1000.0f / 1000.0f;
}