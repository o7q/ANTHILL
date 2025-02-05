#pragma once

#include <vector>
#include <iostream>
#include <cmath>
#include <array>
#include <limits>

#include "../math/bounding_box.hpp"
#include "../math/vector.hpp"
#include "../math/segment.hpp"
#include "../world/world.hpp"
#include "../window/window.hpp"

#include "entity_collision/entity_collision.hpp"

class Entity
{
public:
    Entity(int size_x, int size_y)
    {
        m_size.x = size_x;
        m_size.y = size_y;
        update_bounding_box();
    }

    void setPosition(Vec2<int> position)
    {
        m_position = position;
        update_bounding_box();
    }

    void move(Vec2<int> direction)
    {
        m_position = m_position + direction;
        update_bounding_box();
    }

    void setSize(Vec2<int> size)
    {
        m_size = size;
        update_bounding_box();
    }

    bool **generate_solid_map(const World &world)
    {
        bool **solid_map = new bool *[m_size.y];

        for (int y = 0; y < m_size.y; ++y)
        {
            solid_map[y] = new bool[m_size.x];
        }

        for (int y = 0; y < m_size.y; ++y)
        {
            for (int x = 0; x < m_size.x; ++x)
            {
                int px = m_position.x - m_size.x / 2.0f + x;
                int py = m_position.y - m_size.y / 2.0f + y;

                solid_map[y][x] = world.getParticle(px, py).p_collision_type == Particle::PCollisionType::Solid;
            }
        }

        return solid_map;
    }

    void delete_solid_map(bool **solid_map)
    {
        for (int y = 0; y < m_size.y; ++y)
        {
            if (solid_map[y])
            {
                delete[] solid_map[y];
            }
        }
        if (solid_map)
        {
            delete[] solid_map;
        }
    }

    void resolveWorldCollision(const World &world, Window &window, Camera *camera)
    {
        bool **solid_map = generate_solid_map(world);

        EntityCollision ec(solid_map, m_size);
        ec.convex_optimize(window);
        Vec2<int> resolved_position = ec.getResult(window);

        // move(resolved_position);
        window.debug_renderPoint(m_position.x + resolved_position.x, m_position.y + resolved_position.y, 255, 0, 0, 255);
        BoundingBox bb;
        bb.setSize(m_size.x, m_size.y);
        bb.setPosition(m_position.x + resolved_position.x, m_position.y + resolved_position.y);
        window.debug_renderBoundingBox(bb, 0, 200, 255, 255);

        delete_solid_map(solid_map);
    }

    const BoundingBox &getBoundingBox() const { return m_bounding_box; }

private:
    void update_bounding_box()
    {
        m_bounding_box.setPosition(m_position.x, m_position.y);
        m_bounding_box.setSize(m_size.x, m_size.y);
    }

private:
    Vec2<int> m_position;
    Vec2<int> m_size;

    BoundingBox m_bounding_box;
};