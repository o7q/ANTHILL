#include "living_entity.hpp"

void LivingEntity::update()
{
    m_on_ground = check_ground(1);
    m_speed = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);

    if (m_weapon != nullptr)
    {
        m_weapon->setAimPosition(m_aim_position.x, m_aim_position.y);
    }

    update_x_velocity();
    update_y_velocity();

    move(m_velocity.x, m_velocity.y);

    resolve_world_collision();
}

void LivingEntity::setPosition(float x, float y)
{
    m_position.x = x;
    m_position.y = y;
    update_bounding_box();

    if (m_weapon != nullptr)
    {
        m_weapon->setMuzzlePosition(m_position.x, m_position.y);
    }
}

void LivingEntity::move(float x, float y)
{
    float liquid_damp = in_liquid() ? 3.0f : 1.0f;

    m_position.x += x / liquid_damp;
    m_position.y += y;
    update_bounding_box();

    if (m_weapon != nullptr)
    {
        m_weapon->setMuzzlePosition(m_position.x, m_position.y);
    }
}

void LivingEntity::jump(bool override)
{
    if (!m_on_ground && !override)
    {
        return;
    }

    m_velocity.y = -m_jump_power;
}

void LivingEntity::setJumpPower(float jump_power)
{
    m_jump_power = jump_power;
}