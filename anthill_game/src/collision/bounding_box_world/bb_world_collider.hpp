#pragma once

#include "../../engine/math/vector.hpp"
#include "../../engine/math/bounding_box.hpp"
#include "../../world/world.hpp"

class BBWorldCollider
{
public:
    BBWorldCollider(const BoundingBox &bb) : m_bb(bb) {}

    Vec2<int> resolve(const World *world);

    void setXSensitivity(float x_sensitivity) { m_x_sensitivity = x_sensitivity; }
    void setYSensitivity(float y_sensitivity) { m_y_sensitivity = y_sensitivity; }

private:
    void convex_optimize(const World *world);
    void convex_optimize_pass(Particle p, int x, int y, int x_origin, int y_origin, int y_i);

    int i_x(int x);
    int i_y(int y);

private:
    float m_x_sensitivity = 1.0f;
    float m_y_sensitivity = 1.0f;

private:
    const BoundingBox &m_bb;
    Vec2<int> m_bb_pos;
    Vec2<int> m_bb_size;

private:
    int m_ys[4];
    float m_min_distance = 0.0f;
    Vec2<int> m_resolve_vector;
};