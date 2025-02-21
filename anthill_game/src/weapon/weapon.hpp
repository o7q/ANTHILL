#pragma once

#include <vector>
#include "../engine/math/vector.hpp"
#include "../bullet/bullet.hpp"

class Weapon
{
public:
    struct ShootData
    {
        std::vector<Bullet> bullets;
        Vec2<float> knockback_vector;
    };

public:
    Weapon() {}
    virtual ~Weapon() {}

    virtual ShootData shoot() const
    {
        return ShootData();
    }

    void setMuzzlePosition(float x, float y)
    {
        m_muzzle_position.x = x;
        m_muzzle_position.y = y;
    }

    void setAimPosition(float x, float y)
    {
        m_aim_position.x = x;
        m_aim_position.y = y;
    }

    void setSpeed(float speed)
    {
        m_speed = speed;
    }

    void setPower(float power)
    {
        m_power = power;
    }

    void setKnockbackPower(float knockback_power)
    {
        m_knockback_power = knockback_power;
    }

    Vec2<float> getAimPosition() const { return m_aim_position; }

protected:
    float m_speed = 30.0f;
    float m_power = 5.0f;
    float m_knockback_power = 5.0f;

    Vec2<float> m_muzzle_position;
    Vec2<float> m_aim_position;
};