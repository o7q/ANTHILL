#include "entity.hpp"

bool Entity::check_ground(int y_scan)
{
    Vec2<int> m_bb_pos = m_bounding_box.getPosition();
    Vec2<int> m_bb_size = m_bounding_box.getSize();
    for (int y = 0; y < y_scan; ++y)
    {
        for (int x = 0; x < m_bb_size.x; ++x)
        {
            int _x = m_bb_pos.x - m_bb_size.x / 2 + x;
            int _y = m_bb_pos.y + m_bb_size.y / 2 + y;

            if (m_world.getParticle(_x, _y).p_collision_type == Particle::PCollisionType::Solid)
            {
                return true;
            }
        }
    }

    return false;
}

void Entity::update_y_velocity()
{
    if (!m_is_gravity_affected)
    {
        return;
    }

    if (m_velocity.y < m_terminal_velocity)
    {
        m_velocity.y += m_gravity_strength;
    }

    if (m_on_ground && m_velocity.y > 0)
    {
        m_velocity.y = 0;
    }
}

void Entity::resolve_world_collision()
{
    m_bb_collider.update();
    Vec2<int> resolved_position = m_bb_collider.getResolve();

    if (m_bb_collider.hasCollided())
    {
        move(resolved_position.x, resolved_position.y);
    }
}