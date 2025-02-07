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

void Entity::jump()
{
    if (!m_on_ground)
    {
        return;
    }

    m_velocity.y = -m_jump_power;
}