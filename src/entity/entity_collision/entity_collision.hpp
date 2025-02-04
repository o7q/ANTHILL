#pragma once

#include "../../math/vector.hpp"

class EntityCollision
{
public:
    EntityCollision(bool **world_solid_map, Vec2<int> entity_bounds)
    {
        m_entity_bounds = entity_bounds;
        m_world_solid_map = world_solid_map;

        convex_optimize();
    }

    Vec2<int> getResult() const
    {
        return m_best_point * m_inverse_mult;
    }

private:
    void convex_optimize();
    void convex_optimize_pass(bool is_solid, int x, int y, int max_y_i, int i_x, int i_y);

    int inverse_x(int x);
    int inverse_y(int y);

private:
    bool **m_world_solid_map = nullptr;
    Vec2<int> m_entity_bounds;

    int m_max_ys[4];
    float m_min_distance = 0.0f;
    Vec2<int> m_best_point;
    Vec2<int> m_inverse_mult;
};