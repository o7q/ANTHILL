#include "world.hpp"

#include "../math/random.hpp"

#include <iostream>

void World::update_particles()
{
    for (int y = m_size.y - 1; y >= 0; --y)
    {
        if (Random::genInt(0, 2) == 0)
        {
            for (int x = 0; x < m_size.x; ++x)
            {
                update_particle(x, y);
            }
        }
        else
        {
            for (int x = m_size.x - 1; x >= 0; --x)
            {
                update_particle(x, y);
            }
        }
    }
}

void World::update_particle(int x, int y)
{
    Particle particle = m_particles[y][x];

    switch (m_particles[y][x].p_mode)
    {
    case Particle::PMode::NoGravity:
        break;
    case Particle::PMode::Sand:
        update_sand(particle, x, y);
        break;
    case Particle::PMode::Water:
        update_water(particle, x, y);
        break;
    }
}