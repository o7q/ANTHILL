#include "entity.hpp"

#include <cmath>

bool Entity::check_ground(int y_scan)
{
    Vec2<int> m_bb_pos = m_bounding_box.getPosition().toInt();
    Vec2<int> m_bb_size = m_bounding_box.getSize().toInt();

    for (int y = 0; y < y_scan; ++y)
    {
        for (int x = 0; x < m_bb_size.x; ++x)
        {
            int _x = m_bb_pos.x - m_bb_size.x / 2 + x;
            int _y = m_bb_pos.y + m_bb_size.y / 2 + y;

            for (const World *world : m_worlds)
            {
                Particle p = world->getParticle(_x, _y);
                if (p.p_collision_type == Particle::PCollisionType::Solid && p.solid_enable_collision)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

void Entity::update_x_velocity()
{
    float dt = m_window.time().getDeltaTime();
    float air_resistance_factor = std::exp(-dt * m_air_resistance);
    m_velocity.x *= air_resistance_factor;

    if (std::fabs(m_velocity.x) < 0.25f)
    {
        m_velocity.x = 0.0f;
    }
}

void Entity::update_y_velocity()
{
    if (!m_is_gravity_affected)
    {
        return;
    }

    float dt = m_window.time().getDeltaTime();
    if (m_velocity.y < m_terminal_velocity)
    {
        m_velocity.y += m_gravity_strength * dt;
    }

    if (m_on_ground && m_velocity.y > 0)
    {
        m_velocity.y = 0;
    }
}

void Entity::resolve_world_collision()
{
    for (const World *world : m_worlds)
    {
        m_bb_collider.resolve(world);

        if (m_bb_collider.collided())
        {
            Vec2<int> resolve_vector = m_bb_collider.getResult();
            move(resolve_vector.x, resolve_vector.y);
        }
    }
}