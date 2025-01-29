#include "../world.hpp"

void World::update_water(Particle particle, int x, int y)
{
    const Particle original = particle;
    bool moved = false;

    if (y < m_size.y - 1 && !moved)
    {
        if (m_particles[y + 1][x].isLiquidPassable())
        {
            swap_particle(x, y, x, y + 1);
            moved = true;
        }
    }

    if (x > 0 && !moved)
    {
        if (m_particles[y][x - 1].isLiquidPassable())
        {
            swap_particle(x, y, x - 1, y);
            moved = true;
        }
    }

    if (x < m_size.x - 1 && !moved)
    {
        if (m_particles[y][x + 1].isLiquidPassable())
        {
            swap_particle(x, y, x + 1, y);
            moved = true;
        }
    }
}