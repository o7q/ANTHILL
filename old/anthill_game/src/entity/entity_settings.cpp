#include "entity.hpp"

void Entity::setGravityAffected(bool value)
{
    m_is_gravity_affected = value;
}

void Entity::setGravityStrength(float gravity_strength)
{
    m_gravity_strength = gravity_strength;
}

void Entity::setTerminalVelocity(float terminal_velocity)
{
    m_terminal_velocity = terminal_velocity;
}

void Entity::setBoundsSize(int width, int height)
{
    m_bounds_size.x = width;
    m_bounds_size.y = height;
    update_bounding_box();
}