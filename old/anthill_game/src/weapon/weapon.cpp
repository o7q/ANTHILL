#include "weapon.hpp"

Weapon::ShootData Weapon::shoot() const
{
    return ShootData();
}

void Weapon::setMuzzlePosition(float x, float y)
{
    m_muzzle_position.x = x;
    m_muzzle_position.y = y;
}

void Weapon::setAimPosition(float x, float y)
{
    m_aim_position.x = x;
    m_aim_position.y = y;
}

void Weapon::setSpeed(float speed)
{
    m_speed = speed;
}

void Weapon::setPower(float power)
{
    m_power = power;
}

void Weapon::setKnockbackPower(float knockback_power)
{
    m_knockback_power = knockback_power;
}