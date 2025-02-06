#include "entity_collision.hpp"

#include <cmath>
#include <limits>
#include <iostream>

void EntityCollision::convex_optimize(Window &window)
{
    for (int i = 0; i < 2; ++i)
    {
        m_ys[i] = 0;
        m_ys[i + 2] = m_entity_bounds.y - 1;
    }

    m_min_distance = std::numeric_limits<float>::max();

    for (int x = 0; x < m_entity_bounds.x; ++x)
    {
        for (int y = 0; y < m_entity_bounds.y; ++y)
        {
            convex_optimize_pass(m_world_solid_map[y     ][i_x(x)], i_x(x), y     , 0                    , 0                    , 0);                                         // top-left
            convex_optimize_pass(m_world_solid_map[y     ][x     ], x     , y     , m_entity_bounds.x - 1, 0                    , 1);                               // top-right
            convex_optimize_pass(m_world_solid_map[i_y(y)][x     ], x     , i_y(y), m_entity_bounds.x - 1, m_entity_bounds.y - 1, 2); // bottom-right
            convex_optimize_pass(m_world_solid_map[i_y(y)][i_x(x)], i_x(x), i_y(y), 0                    , m_entity_bounds.y - 1, 3);           // bottom-left
        }
    }
}

void EntityCollision::convex_optimize_pass(bool is_solid, int x, int y, int x_origin, int y_origin, int corner_index)
{
    bool is_top = corner_index <= 1;
    bool is_bottom = corner_index >= 2;

    if (!is_solid)
    {
        if ((m_ys[corner_index] != y && is_top) ||
            (m_ys[corner_index] != y && is_bottom))
        {
            return;
        }
    }

    // 0   1
    //  [ ]
    // 3   2

    if ((m_ys[corner_index] <= y && is_top) ||
        (m_ys[corner_index] >= y && is_bottom))
    {
        m_ys[corner_index] = y;

        float d = std::sqrt(
            std::pow(x - x_origin, 2) +
            std::pow(y - y_origin, 2) * 0.5f);

        if (m_min_distance >= d)
        {
            m_min_distance = d;
            m_resolve_vector = Vec2<int>(x - x_origin, y - y_origin);
        }
    }
}