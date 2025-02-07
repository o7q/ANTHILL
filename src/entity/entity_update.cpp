#include "entity.hpp"

void Entity::update()
{
    check_ground();
    update_y_velocity();
    move(m_velocity.x, m_velocity.y);
    resolve_world_collision();
}

void Entity::update_bounding_box()
{
    m_bounding_box.setPosition(m_position.x, m_position.y);
    m_bounding_box.setSize(m_bounds_size.x, m_bounds_size.y);
}