#include "world_physics.hpp"

#include "../engine/math/color.hpp"

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