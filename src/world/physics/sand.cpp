#include "../world.hpp"

void World::update_sand(Particle particle, int x, int y)
{
    const Particle original = particle;
    bool moved = false;

    if (y < m_size.y - 1 && !moved)
    {
        if (m_particles[y + 1][x].isSolidPassable())
        {
            swap_particle(x, y, x, y + 1);
        }
    }

    if (x > 0 && y < m_size.y - 1 && !moved)
    {
        if (m_particles[y + 1][x - 1].isSolidPassable())
        {
            swap_particle(x, y, x - 1, y + 1);
        }
    }

    if (x < m_size.x - 1 && y < m_size.y - 1 && !moved)
    {
        if (m_particles[y + 1][x + 1].isSolidPassable())
        {
            swap_particle(x, y, x + 1, y + 1);
        }
    }
}