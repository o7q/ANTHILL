#include "world_physics.hpp"

#include <algorithm>

#include "../engine/math/vector.hpp"
#include "../engine/math/random.hpp"
#include "../engine/math/bounding_box.hpp"

void WorldPhysics::updateParticles(BoundingBox *box)
{
    int y_start = 0;
    int y_end = 0;

    int x1_start = 0;
    int x1_end = 0;

    int x2_start = 0;
    int x2_end = 0;

    if (box != nullptr)
    {
        y_start  = std::clamp(box->getP4().toInt().y, 0, m_size.y - 1);
        y_end    = std::clamp(box->getP1().toInt().y, 0, m_size.y - 1);

        x1_start = std::clamp(box->getP1().toInt().x, 0, m_size.x - 1);
        x1_end   = std::clamp(box->getP2().toInt().x, 0, m_size.x - 1);

        x2_start = x1_end;
        x2_end   = x1_start;
    }
    else
    {
        y_start  = m_size.y - 1;
        y_end    = 0;

        x1_start = 0;
        x1_end   = m_size.x;

        x2_start = m_size.x - 1;
        x2_end   = 0;
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
    bool x_too_big   = x >= m_size.x;
    bool x_too_small = x < 0;

    bool y_too_big   = y >= m_size.y;
    bool y_too_small = y < 0;

    if (x_too_big || x_too_small || y_too_big || y_too_small)
    {
        bool can_portal_left  = x_too_small && (!y_too_big || !y_too_small) && m_portal.left ->m_size.y == m_size.y;
        bool can_portal_right = x_too_big   && (!y_too_big || !y_too_small) && m_portal.right->m_size.y == m_size.y;
        bool can_portal_up    = y_too_small && (!x_too_big || !x_too_small) && m_portal.up   ->m_size.x == m_size.x;
        bool can_portal_down  = y_too_big   && (!x_too_big || !x_too_small) && m_portal.down ->m_size.x == m_size.x;

        if (can_portal_left)
        {
            m_portal.left->p_set(x + m_portal.left->m_size.x, y, particle);
        }
        if (can_portal_right)
        {
            float x_overshoot = x - m_size.x;
            m_portal.right->p_set(x_overshoot, y, particle);
        }
        if (can_portal_up)
        {
            m_portal.up->p_set(x, y + m_portal.up->m_size.y, particle);
        }
        if (can_portal_down)
        {
            float y_overshoot = y - m_size.y;
            m_portal.down->p_set(x, y_overshoot, particle);
        }

        return;
    }

    m_particles[y][x] = particle;

    if (m_world_texture != nullptr)
    {
        m_world_texture->setPixel(x, y, particle.color.hex());
    }
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
    Uint8 c_r =             (a.r * mult_a + b.r * mult_b) / div;
    Uint8 c_g =             (a.g * mult_a + b.g * mult_b) / div;
    Uint8 c_b =             (a.b * mult_a + b.b * mult_b) / div;
    Uint8 c_a = mix_alpha ? (a.a * mult_a + b.a * mult_b) / div : a.a;
    
    return Color(c_r, c_g, c_b, c_a);
}

Particle WorldPhysics::p_get(int x, int y)
{
    bool x_too_big   = x >= m_size.x;
    bool x_too_small = x < 0;

    bool y_too_big   = y >= m_size.y;
    bool y_too_small = y < 0;

    if (x_too_big || x_too_small || y_too_big || y_too_small)
    {
        bool can_portal_left  = x_too_small && (!y_too_big || !y_too_small) && m_portal.left ->m_size.y == m_size.y;
        bool can_portal_right = x_too_big   && (!y_too_big || !y_too_small) && m_portal.right->m_size.y == m_size.y;
        bool can_portal_up    = y_too_small && (!x_too_big || !x_too_small) && m_portal.up   ->m_size.x == m_size.x;
        bool can_portal_down  = y_too_big   && (!x_too_big || !x_too_small) && m_portal.down ->m_size.x == m_size.x;

        if (can_portal_left)
        {
            return m_portal.left->p_get(x + m_portal.left->m_size.x, y);
        }
        if (can_portal_right)
        {
            float x_overshoot = x - m_size.x;
            return m_portal.right->p_get(x_overshoot, y);
        }
        if (can_portal_up)
        {
            return m_portal.up->p_get(x, y + m_portal.up->m_size.y);
        }
        if (can_portal_down)
        {
            float y_overshoot = y - m_size.y;
            return m_portal.down->p_get(x, y_overshoot);
        }

        return Particle();
    }

    return m_particles[y][x];
}

bool WorldPhysics::in_bounds(int x, int y)
{
    bool y_can_up    = (y >= 0)       || (m_portal.up    != nullptr);
    bool y_can_down  = (y < m_size.y) || (m_portal.down  != nullptr);
    bool x_can_left  = (x >= 0)       || (m_portal.left  != nullptr);
    bool x_can_right = (x < m_size.x) || (m_portal.right != nullptr);

    return y_can_up && y_can_down && x_can_left && x_can_right;
}

void WorldPhysics::setPortal(Portal portal)
{
    m_portal = portal;
}

void WorldPhysics::setWorldTexture(Texture *world_texture)
{
    m_world_texture = world_texture;
}