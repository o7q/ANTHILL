#include "entity.hpp"

void Entity::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
    update_bounding_box();
}

void Entity::move(float x, float y)
{
    m_position.x = m_position.x + x;
    m_position.y = m_position.y + y;
    update_bounding_box();
}

void Entity::jump(bool override)
{
    if (check_ground(30) && !m_jump_buffered)
    {
        m_jump_buffered = true;
    }

    if (!m_on_ground && !override)
    {
        return;
    }

    m_velocity.y = -m_jump_power;
    m_jump_buffered = false;
}