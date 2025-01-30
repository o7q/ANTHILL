#include "../world_physics.hpp"

void WorldPhysics::update_water(Particle particle, int x, int y)
{
    // const Particle original = particle;
    bool moved = false;

    if (in_bounds(x, y + 1) && !moved)
    {
        if (m_particles[y + 1][x].isLiquidPassable())
        {
            p_swap(x, y, x, y + 1);
            moved = true;
        }
    }

    if (in_bounds(x - 1, y) && !moved)
    {
        if (m_particles[y][x - 1].isLiquidPassable())
        {
            p_swap(x, y, x - 1, y);
            moved = true;
        }
    }

    if (in_bounds(x + 1, y) && !moved)
    {
        if (m_particles[y][x + 1].isLiquidPassable())
        {
            p_swap(x, y, x + 1, y);
            moved = true;
        }
    }
}