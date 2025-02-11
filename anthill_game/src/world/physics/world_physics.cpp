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
    bool x_too_big = x >= m_size.x;
    bool x_too_small = x < 0;

    bool y_too_big = y >= m_size.y;
    bool y_too_small = y < 0;

    if (x_too_big || x_too_small || y_too_big || y_too_small)
    {
        int other_x = x;
        int other_y = y;

        if (x_too_big)
        {
            other_x = x - m_physics_portal->m_size.x;
        }
        if (x_too_small)
        {
            other_x = x + m_physics_portal->m_size.x;
        }
        if (y_too_big)
        {
            other_y = y - m_physics_portal->m_size.y;
        }
        if (y_too_small)
        {
            other_y = y + m_physics_portal->m_size.y;
        }

        m_physics_portal->p_set(other_x, other_y, particle);
        return;
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
    bool x_too_big = x >= m_size.x;
    bool x_too_small = x < 0;

    bool y_too_big = y >= m_size.y;
    bool y_too_small = y < 0;

    if (x_too_big || x_too_small || y_too_big || y_too_small)
    {
        int other_x = x;
        int other_y = y;

        if (x_too_big)
        {
            other_x = x - m_physics_portal->m_size.x;
        }
        if (x_too_small)
        {
            other_x = x + m_physics_portal->m_size.x;
        }
        if (y_too_big)
        {
            other_y = y - m_physics_portal->m_size.y;
        }
        if (y_too_small)
        {
            other_y = y + m_physics_portal->m_size.y;
        }

        return m_physics_portal->p_get(other_x, other_y);
    }

    return m_particles[y][x];
}

bool WorldPhysics::in_bounds(int x, int y)
{
    bool portal_assigned = m_physics_portal != nullptr;

    bool y_can_up = (y >= 0) || (portal_assigned && m_portal_up);
    bool y_can_down = (y < m_size.y) || (portal_assigned && m_portal_down);
    bool x_can_left = (x >= 0) || (portal_assigned && m_portal_left);
    bool x_can_right = (x < m_size.x) || (portal_assigned && m_portal_right);

    return y_can_up && y_can_down && x_can_left && x_can_right;
}