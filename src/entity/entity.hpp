#pragma once

#include <vector>
#include <iostream>
#include <cmath>

#include "../math/bounding_box.hpp"
#include "../math/vector.hpp"
#include "../math/segment.hpp"
#include "../world/world.hpp"

class Entity
{
public:
    Entity(float size_x, float size_y)
    {
        m_size.x = size_x;
        m_size.y = size_y;
        update_bounding_box();
    }

    void setPosition(Vec2<float> position)
    {
        m_position = position;
        update_bounding_box();
    }

    void move(Vec2<float> direction)
    {
        m_position = m_position + direction;
        update_bounding_box();
    }

    void setSize(Vec2<float> size)
    {
        m_size = size;
        update_bounding_box();
    }

    void update()
    {
    }

    void resolveWorldCollision(const std::vector<Segment> &worldCollisionSegments)
    {
        float max_x_offset = 0.0f;
        float max_y_offset = 0.0f;

        bool collision_occurred = false;

        for (const Segment &segment : worldCollisionSegments)
        {
            Vec2<float> point = Vec2<float>(
                (segment.a.x + segment.b.x) / 2.0f,
                (segment.a.y + segment.b.y) / 2.0f);

            const Vec2<float> p1 = m_bounding_box.getP1();
            const Vec2<float> p3 = m_bounding_box.getP3();

            bool is_point_colliding = point.x > p1.x &&
                                      point.y > p1.y &&
                                      point.x < p3.x &&
                                      point.y < p3.y;

            if (is_point_colliding)
            {
                collision_occurred = true;
            }
            else
            {
                continue;
            }

            Vec2<float> r_offset;
            float c_depth_x = std::fabs(point.x - m_position.x) - m_size.x / 2.0f;
            float c_depth_y = std::fabs(point.y - m_position.y) - m_size.y / 2.0f;

            c_depth_x *= -1.0f;
            c_depth_y *= -1.0f;

            c_depth_x = point.x > m_position.x ? -c_depth_x : c_depth_x;
            c_depth_y = point.y > m_position.y ? -c_depth_y : c_depth_y;

            if (std::fabs(c_depth_x) > std::fabs(max_x_offset))
            {
                max_x_offset = c_depth_x;
            }

            if (std::fabs(c_depth_y) > std::fabs(max_y_offset))
            {
                max_y_offset = c_depth_y;
            }
        }

        if (!collision_occurred)
        {
            return;
        }

        Vec2<float> r_offset;
        if (std::fabs(max_x_offset) < std::fabs(max_y_offset))
        {
            r_offset.x = max_x_offset;
            r_offset.y = 0.0f;
        }
        else
        {
            r_offset.x = 0.0f;
            r_offset.y = max_y_offset;
        }

        std::cout << "x: " << max_x_offset << "   y: " << max_y_offset << std::endl;

        move(r_offset);
    }

    const BoundingBox &getBoundingBox() const { return m_bounding_box; }

private:
    void update_bounding_box()
    {
        m_bounding_box.setPosition(m_position.x, m_position.y);
        m_bounding_box.setSize(m_size.x, m_size.y);
    }

private:
    Vec2<float> m_position;
    Vec2<float> m_size;

    BoundingBox m_bounding_box;
};