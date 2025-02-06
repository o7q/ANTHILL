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
    Entity(const World &world) : world(world) {}

    void update()
    {
        m_on_ground = false;
        for (int i = 0; i < m_bounding_box.getSize().x; ++i)
        {
            int x = m_bounding_box.getPosition().x - m_bounding_box.getSize().x / 2 + i;
            int y = m_bounding_box.getPosition().y + m_bounding_box.getSize().y / 2;

            if (world.getParticle(x, y).p_collision_type == Particle::PCollisionType::Solid)
            {
                m_on_ground = true;
            }
        }

        std::cout << m_on_ground << std::endl;

        if (m_velocity.y < terminal_velocity)
        {
            m_velocity.y += gravity;
        }

        if (m_on_ground && m_velocity.y > 0)
        {
            m_velocity.y = 0;
        }

        move(m_velocity.x, m_velocity.y);
    }

    void jump()
    {
        if (m_on_ground)
        {
            m_velocity.y = -8.0f;
        }
    }

    void setPosition(int x, int y)
    {
        m_position.x = x;
        m_position.y = y;
        update_bounding_box();
    }

    void move(int x, int y)
    {
        m_position.x = m_position.x + x;
        m_position.y = m_position.y + y;
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
        ec.setYSensitivity(4.0f);
        Vec2<int> resolved_position = ec.resolve();

        if (ec.collided())
        {
            move(resolved_position.x, resolved_position.y);
        }
    }

    const BoundingBox &getBoundingBox() const { return m_bounding_box; }

protected:
    const World &world;

    Vec2<int> m_position;
    Vec2<int> m_size;
    Vec2<float> m_velocity;

    const float terminal_velocity = 5.0f;
    const float gravity = 0.5f;

    bool m_on_ground;

    BoundingBox m_bounding_box;

private:
    void update_bounding_box()
    {
        m_bounding_box.setPosition(m_position.x, m_position.y);
        m_bounding_box.setSize(m_size.x, m_size.y);
    }
};