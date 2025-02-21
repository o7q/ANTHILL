#include "living_entity.hpp"

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