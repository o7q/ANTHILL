#include "world_physics.hpp"

#include "../math/random.hpp"

void WorldPhysics::update_particles()
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

void WorldPhysics::update_particle(int x, int y)
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

void WorldPhysics::p_set(int x, int y, Particle particle)
{
    m_particles[y][x] = particle;
    m_world_texture->setPixel(x, y, particle.color.hex());
}

void WorldPhysics::p_swap(int x1, int y1, int x2, int y2)
{
    Particle temp = m_particles[y2][x2];
    p_set(x2, y2, m_particles[y1][x1]);
    p_set(x1, y1, temp);
}

Color WorldPhysics::p_mix(Color a, Color b, float mult_a, float mult_b, float div, bool mixAlpha)
{
    return Color((a.r * mult_a + b.r * mult_b) / div,
                 (a.g * mult_a + b.g * mult_b) / div,
                 (a.b * mult_a + b.b * mult_b) / div,
                 mixAlpha ? (a.a * mult_a + b.a * mult_b) / div : a.a);
}

Particle WorldPhysics::p_get(int x, int y)
{
    return m_particles[y][x];
}

bool WorldPhysics::in_bounds(int x, int y)
{
    return x >= 0 && x < m_size.x && y >= 0 && y < m_size.y;
}