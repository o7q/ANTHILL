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

#include "../collision/bounding_box_world/bb_world_resolver.hpp"

class Entity
{
public:
    void setPosition(int x, int y)
    {
        m_position.x = x;
        m_position.y = y;
        update_bounding_box();
    }

    void move(Vec2<int> direction)
    {
        m_position = m_position + direction;
        update_bounding_box();
    }

    void setSize(int width, int height)
    {
        m_size.x = width;
        m_size.y = height;
        update_bounding_box();
    }

    void resolveWorldCollision(const World &world)
    {
        BBWorldResolver ec(world, m_bounding_box);
        ec.setYSensitivity(2.0f);
        Vec2<int> resolved_position = ec.resolve();

        move(resolved_position);
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