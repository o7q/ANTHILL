#include "entity_collision.hpp"

#include <cmath>
#include <limits>

void EntityCollision::convex_optimize()
{
    for (int i = 0; i < 4; ++i)
        m_max_ys[i] = std::numeric_limits<int>::min();

    m_min_distance = std::numeric_limits<float>::max();

    for (int x = 0; x < m_entity_bounds.x; ++x)
    {
        for (int y = 0; y < m_entity_bounds.y; ++y)
        {
            if (m_world_solid_map[y][x])
            {
                // window.debug_renderPoint(x, y, 0, 100, 255, 255);
            }

            convex_optimize_pass(m_world_solid_map[y][inverse_x(x)], inverse_x(x), y, 0, 1, 1);             // top-left
            convex_optimize_pass(m_world_solid_map[y][x], inverse_x(x), y, 1, -1, 1);                       // top-right
            convex_optimize_pass(m_world_solid_map[inverse_y(y)][x], inverse_x(x), y, 2, -1, -1);           // bottom-right
            convex_optimize_pass(m_world_solid_map[inverse_y(y)][inverse_x(x)], inverse_x(x), y, 3, 1, -1); // bottom-left
        }
    }
}

void EntityCollision::convex_optimize_pass(bool is_solid, int x, int y, int max_y_i, int i_x, int i_y)
{
    if (!is_solid)
    {
        return;
    }

    if (m_max_ys[max_y_i] < y)
    {
        m_max_ys[max_y_i] = y;

        float d = std::sqrt(x * x + y * y);
        if (m_min_distance > d)
        {
            m_min_distance = d;

            m_best_point = Vec2<int>(x, y);
            m_inverse_mult = Vec2<int>(i_x, i_y);
        }
    }
}