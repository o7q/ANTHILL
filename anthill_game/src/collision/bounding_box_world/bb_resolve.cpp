#include "bb_world_collider.hpp"

#include <cmath>
#include <limits>

void BBWorldCollider::convex_optimize(const World *world)
{
    for (int i = 0; i < 2; ++i)
    {
        m_ys[i    ] = 0;
        m_ys[i + 2] = m_bb_size.y - 1;
    }

    m_min_distance = std::numeric_limits<float>::max();

    int local_x = m_bb_pos.x - m_bb_size.x / 2.0f;
    int local_y = m_bb_pos.y - m_bb_size.y / 2.0f;

    for (int x = 0; x < m_bb_size.x; ++x)
    {
        for (int y = 0; y < m_bb_size.y; ++y)
        {
            int wx = local_x + x;
            int wy = local_y + y;

            int i_wx = local_x + i_x(x);
            int i_wy = local_y + i_y(y);

            convex_optimize_pass(world->getParticle(i_wx,   wy), i_x(x), y     , 0              , 0              , 0); // top-left
            convex_optimize_pass(world->getParticle(  wx,   wy), x     , y     , m_bb_size.x - 1, 0              , 1); // top-right
            convex_optimize_pass(world->getParticle(  wx, i_wy), x     , i_y(y), m_bb_size.x - 1, m_bb_size.y - 1, 2); // bottom-right
            convex_optimize_pass(world->getParticle(i_wx, i_wy), i_x(x), i_y(y), 0              , m_bb_size.y - 1, 3); // bottom-left
        }
    }
}

void BBWorldCollider::convex_optimize_pass(Particle p, int x, int y, int x_origin, int y_origin, int corner_index)
{
    // 0   1
    //  [ ]
    // 3   2

    bool is_top = corner_index <= 1;
    bool is_bottom = corner_index >= 2;

    if (p.p_collision_type != Particle::PCollisionType::Solid || !p.solid_enable_collision)
    {
        if ((m_ys[corner_index] != y && is_top) ||
            (m_ys[corner_index] != y && is_bottom))
        {
            return;
        }
    }

    if ((m_ys[corner_index] <= y && is_top) ||
        (m_ys[corner_index] >= y && is_bottom))
    {
        m_ys[corner_index] = y;

        float d = std::sqrt(
            std::pow(x - x_origin, 2) * (1.0f / m_x_sensitivity)+
            std::pow(y - y_origin, 2) * (1.0f / m_y_sensitivity));

        if (m_min_distance >= d)
        {
            m_min_distance = d;
            m_resolve = Vec2<int>(x - x_origin, y - y_origin);
        }
    }
}