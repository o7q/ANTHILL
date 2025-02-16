#pragma once

#include <cmath>
#include <vector>

#include "../engine/math/vector.hpp"
#include "../engine/math/segment.hpp"

#include "../world/world.hpp"
#include "../engine/window/window.hpp"

class Bullet
{
public:
    Bullet(float start_x, float start_y, float target_x, float target_y)
    {
        float x = target_x - start_x;
        float y = target_y - start_y;

        float m = std::sqrt(x * x + y * y);

        m_dx = x / m;
        m_dy = y / m;

        m_position.x = start_x;
        m_position.y = start_y;
    }

    void setSpeed(float speed) { m_speed = speed; }
    void setPower(float power) { m_power = power; }

    float getPower() const { return m_power; }

    bool hit() const { return m_hit; }

    void update(float dt)
    {
        if (m_hit)
        {
            return;
        }

        m_position.x += m_dx * m_speed * dt;
        m_position.y += m_dy * m_speed * dt;
    }

    bool checkWorldHit(const World *world, float dt)
    {
        if (m_hit)
        {
            return false;
        }

        Vec2<float> future_position = m_position + Vec2<float>(m_dx, m_dy) * m_speed * dt;
        Segment bullet_trajectory(m_position, future_position);

        for (const Segment &segment : world->getWorldHitbox())
        {
            Segment::IData i_data = bullet_trajectory.checkSegmentIntersection(segment);
            if (i_data.intersecting)
            {
                m_position = i_data.position;
                m_hit = true;
                return true;
            }
        }

        if (world->getParticle(m_position.x, m_position.y).p_collision_type == Particle::PCollisionType::Solid)
        {
            m_hit = true;
            return true;
        }

        return false;
    }

    Vec2<float> getPosition() const { return m_position; }

private:
    Vec2<float> m_position;

    float m_dx = 0.0f;
    float m_dy = 0.0f;

    float m_speed = 1.0f;
    float m_power = 1.0f;

    bool m_hit = false;
};