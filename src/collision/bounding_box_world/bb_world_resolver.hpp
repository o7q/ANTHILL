#pragma once

#include "../../math/vector.hpp"
#include "../../world/world.hpp"
#include "../../math/bounding_box.hpp"

class BBWorldResolver
{
public:
    BBWorldResolver(const World &world, BoundingBox bb) : m_world(world)
    {
        m_bb_pos = bb.getPosition();
        m_bb_size = bb.getSize();
    }

    Vec2<int> resolve()
    {
        convex_optimize();
        return m_resolve_vector;
    }

    void setXSensitivity(float x_sensitivity)
    {
        m_x_sensitivity = x_sensitivity;
    }

    void setYSensitivity(float y_sensitivity)
    {
        m_y_sensitivity = y_sensitivity;
    }

private:
    void convex_optimize();
    void convex_optimize_pass(Particle p, int x, int y, int x_origin, int y_origin, int y_i);

    int i_x(int x);
    int i_y(int y);

private:
    float m_x_sensitivity = 1.0f;
    float m_y_sensitivity = 1.0f;

private:
    const World &m_world;
    Vec2<int> m_bb_pos;
    Vec2<int> m_bb_size;

private:
    int m_ys[4];
    float m_min_distance = 0.0f;
    Vec2<int> m_resolve_vector;
};