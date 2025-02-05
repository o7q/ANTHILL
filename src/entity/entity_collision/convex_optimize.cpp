#include "entity_collision.hpp"

#include <cmath>
#include <limits>
#include <iostream>

void EntityCollision::convex_optimize(Window &window)
{
    for (int i = 0; i < 2; ++i)
    {
        m_ys[i] = std::numeric_limits<int>::min();
        m_ys[i + 2] = std::numeric_limits<int>::max();
    }

    m_min_distance = std::numeric_limits<float>::max();

    for (int x = 0; x < m_entity_bounds.x; ++x)
    {
        for (int y = 0; y < m_entity_bounds.y; ++y)
        {
            convex_optimize_pass(m_world_solid_map[y][i_x(x)], i_x(x), y, 0, 0, 0, window);                                         // top-left
            convex_optimize_pass(m_world_solid_map[y][x], x, y, m_entity_bounds.x - 1, 0, 1, window);                               // top-right
            convex_optimize_pass(m_world_solid_map[i_y(y)][x], x, i_y(y), m_entity_bounds.x - 1, m_entity_bounds.y - 1, 2, window); // bottom-right
            convex_optimize_pass(m_world_solid_map[i_y(y)][i_x(x)], i_x(x), i_y(y), 0, m_entity_bounds.y - 1, 3, window);           // bottom-left
        }
        std::cout << std::endl;
    }

    std::cout << "\n\n\n\n\n\n"
              << std::endl;
}

void EntityCollision::convex_optimize_pass(bool is_solid, int x, int y, int x_origin, int y_origin, int y_i, Window &window)
{
    if (!is_solid)
    {
        return;
    }

    if ((m_ys[y_i] <= y && y_i <= 1) ||
        (m_ys[y_i] >= y && y_i >= 2))
    {
        m_ys[y_i] = y;

        float d = std::sqrt(
            std::pow(x - x_origin, 2) +
            std::pow(y - y_origin, 2));

        window.debug_renderPoint(x, y, 255, 0, 0, 255);

        if (m_min_distance >= d)
        {
            m_min_distance = d;

            m_resolve_vector = Vec2<int>(x - x_origin, y - y_origin);

            std::cout << x << " " << y << " " << d << std::endl;
            std::cout << x - x_origin << " " << y - y_origin << std::endl;
            // m_inverse_mult = Vec2<int>(x_mult, y_mult);
        }
    }
}