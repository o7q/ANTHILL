#include "entity.hpp"

void Entity::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
    update_bounding_box();

    if (m_weapon != nullptr)
    {
        m_weapon->setMuzzlePosition(m_position.x, m_position.y);
    }
}

void Entity::move(float x, float y)
{
    m_position.x += x;
    m_position.y += y;
    update_bounding_box();

    if (m_weapon != nullptr)
    {
        m_weapon->setMuzzlePosition(m_position.x, m_position.y);
    }
}

void Entity::setXVelocity(float x)
{
    m_velocity.x = x;
}

void Entity::setYVelocity(float y)
{
    m_velocity.y = y;
}

void Entity::jump(bool override)
{
    if (!m_on_ground && !override)
    {
        return;
    }

    m_velocity.y = -m_jump_power;
}