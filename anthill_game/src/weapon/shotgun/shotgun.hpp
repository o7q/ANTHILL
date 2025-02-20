#pragma once

#include <iostream>

#include <cmath>
#include "../../engine/math/angle.hpp"
#include "../weapon.hpp"

class Shotgun : public Weapon
{
    virtual ShootData shoot() const override
    {
        float dx = m_aim_position.x - m_muzzle_position.x;
        float dy = m_aim_position.y - m_muzzle_position.y;

        float aim_angle = std::atan2(dy, dx);
        float spread_angle = degreesToRadians(m_spread);

        ShootData shoot_data;
        shoot_data.aim_angle = aim_angle;

        for (int i = -m_bullet_count / 2; i <= m_bullet_count / 2; ++i)
        {
            float a = aim_angle + i * spread_angle / m_bullet_count;
            shoot_data.bullet_directions.push_back(Vec2<float>(m_muzzle_position.x + std::cos(a), m_muzzle_position.y + std::sin(a)));
        }

        return shoot_data;
    }

protected:
    float m_spread = 15.0f;
    int m_bullet_count = 10;
};