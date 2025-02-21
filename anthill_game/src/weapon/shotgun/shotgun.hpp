#pragma once

#include <iostream>

#include <cmath>
#include "../../engine/math/angle.hpp"
#include "../../bullet/bullet.hpp"
#include "../weapon.hpp"

class Shotgun : public Weapon
{
    virtual ~Shotgun() {}

    virtual ShootData shoot() const override
    {
        float dx = m_aim_position.x - m_muzzle_position.x;
        float dy = m_aim_position.y - m_muzzle_position.y;

        float aim_angle = std::atan2(dy, dx);
        float spread_angle = degreesToRadians(m_spread);

        ShootData shoot_data;
        shoot_data.knockback_vector = Vec2<float>(-std::cos(aim_angle) * m_knockback_power, -std::sin(aim_angle) * m_knockback_power);

        for (int i = -m_bullet_count / 2; i <= m_bullet_count / 2; ++i)
        {
            float a = aim_angle + i * spread_angle / m_bullet_count;

            Vec2<float> direction(m_muzzle_position.x + std::cos(a), m_muzzle_position.y + std::sin(a));
            Bullet bullet(m_muzzle_position.x, m_muzzle_position.y, direction.x, direction.y);

            bullet.setPower(m_power);
            bullet.setSpeed(m_speed);

            shoot_data.bullets.push_back(bullet);
        }

        return shoot_data;
    }

protected:
    float m_spread = 15.0f;
    int m_bullet_count = 10;
};