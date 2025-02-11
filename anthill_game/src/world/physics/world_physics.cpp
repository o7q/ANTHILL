#include "world_physics.hpp"

#include <algorithm>

#include "../../math/random.hpp"
#include "../../math/bounding_box.hpp"
#include "../../math/vector.hpp"

void WorldPhysics::update_particles(BoundingBox *box)
{
    int y_start = 0;
    int y_end = 0;

    int x1_start = 0;
    int x1_end = 0;

    int x2_start = 0;
    int x2_end = 0;

    if (box != nullptr)
    {
        y_start = std::clamp(box->getP4().y, 0, m_size.y - 1);
        y_end = std::clamp(box->getP1().y, 0, m_size.y - 1);

        x1_start = std::clamp(box->getP1().x, 0, m_size.x - 1);
        x1_end = std::clamp(box->getP2().x, 0, m_size.x - 1);

        x2_start = x1_end;
        x2_end = x1_start;
    }
    else
    {
        y_start = m_size.y - 1;
        y_end = 0;

        x1_start = 0;
        x1_end = m_size.x;

        x2_start = m_size.x - 1;
        x2_end = 0;
    }

    for (int y = y_start; y >= y_end; --y)
    {
        if (Random::genInt(0, 2) == 0)
        {
            for (int x = x1_start; x < x1_end; ++x)
            {
                update_particle(x, y);
            }
        }
        else
        {
            for (int x = x2_start; x >= x2_end; --x)
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
    case Particle::PMode::None:
        break;
    case Particle::PMode::Sand:
        update_sand(particle, x, y);
        break;
    case Particle::PMode::Water:
        update_water(particle, x, y);
        break;
    case Particle::PMode::Smoke:
        update_smoke(particle, x, y);
        break;
    case Particle::PMode::Goop:
        update_goop(particle, x, y);
        break;
    }
}

void WorldPhysics::p_set(int x, int y, Particle particle)
{
    if (!in_bounds(x, y))
    {
        return;
    }

    if (y >= m_size.y)
    {
        return m_physics_portal->p_set(x, 0, particle);
    }

    if (y < 0)
    {
        return m_physics_portal->p_set(x, m_physics_portal->m_size.y - 1, particle);
    }

    m_particles[y][x] = particle;
    m_world_texture->setPixel(x, y, particle.color.hex());
}

void WorldPhysics::p_swap(int x1, int y1, int x2, int y2)
{
    Particle temp = p_get(x2, y2);
    p_set(x2, y2, m_particles[y1][x1]);
    p_set(x1, y1, temp);
}

void WorldPhysics::p_move(int x1, int y1, int x2, int y2)
{
    Particle temp = p_get(x1, y1);
    p_set(x2, y2, temp);
    p_set(x1, y1, Particle());
}

Color WorldPhysics::p_mix(Color a, Color b, float mult_a, float mult_b, float div, bool mix_alpha)
{
    return Color((a.r * mult_a + b.r * mult_b) / div,
                 (a.g * mult_a + b.g * mult_b) / div,
                 (a.b * mult_a + b.b * mult_b) / div,
                 mix_alpha ? (a.a * mult_a + b.a * mult_b) / div : a.a);
}

Particle WorldPhysics::p_get(int x, int y)
{
    if (!in_bounds(x, y))
    {
        return Particle();
    }

    if (y >= m_size.y)
    {
        return m_physics_portal->p_get(x, 0);
    }

    if (y < 0)
    {
        return m_physics_portal->p_get(x, m_physics_portal->m_size.y - 1);
    }

    return m_particles[y][x];
}

bool WorldPhysics::in_bounds(int x, int y)
{
    bool x_in_bound = x >= 0 && x < m_size.x;
    bool y_in_bound =(y >= 0 && y < m_size.y) || (m_physics_portal != nullptr);
    return x_in_bound && y_in_bound;
}