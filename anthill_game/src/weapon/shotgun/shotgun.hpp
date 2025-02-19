#pragma once

#include <cmath>
#include "../weapon.hpp"

class Shotgun : public Weapon
{
    virtual std::vector<Vec2<float>> shoot() const override
    {
        float dx = m_aim_position.x - m_muzzle_position.x;
        float dy = m_aim_position.y - m_muzzle_position.y;

        float angle = std::atan2(dy, dx);

        float spread_angle = 15.0f;
        int samples = 10;

        std::vector<Vec2<float>> aim_positions;

        for (int i = -samples / 2; i < samples / 2; ++i)
        {
            float a = angle + i * spread_angle / samples;

            Vec2<float> aim(m_aim_position.x + std::cos(a), m_aim_position.y + std::sin(a));
            aim_positions.push_back(aim);
        }

        return aim_positions;
    }
};