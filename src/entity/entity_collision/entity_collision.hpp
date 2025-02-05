#pragma once

#include "../../math/vector.hpp"
#include "../../window/window.hpp"

class EntityCollision
{
public:
    EntityCollision(bool **world_solid_map, Vec2<int> entity_bounds)
    {
        m_entity_bounds = entity_bounds;
        m_world_solid_map = world_solid_map;
    }

    Vec2<int> getResult(Window &window) const
    {
        return m_resolve_vector;
    }

    void convex_optimize(Window &window);

private:
    void convex_optimize_pass(bool is_solid, int x, int y, int x_origin, int y_origin, int y_i, Window &window);

    int i_x(int x);
    int i_y(int y);

private:
    bool **m_world_solid_map = nullptr;
    Vec2<int> m_entity_bounds;

    int m_ys[4];
    float m_min_distance = 0.0f;
    Vec2<int> m_resolve_vector;
    Vec2<int> m_inverse_mult;
};