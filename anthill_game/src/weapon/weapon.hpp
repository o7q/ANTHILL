#pragma once

#include <vector>
#include "../engine/math/vector.hpp"

class Weapon
{
public:
    Weapon()
    {
    }

    virtual std::vector<Vec2<float>> shoot() const
    {
        return std::vector<Vec2<float>>();
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

    Vec2<float> getMuzzlePosition() const
    {
        return m_muzzle_position;
    }

    Vec2<float> getAimPosition() const
    {
        return m_aim_position;
    }

    float getSpeed() const
    {
        return m_speed;
    }

    float getPower() const
    {
        return m_power;
    }

protected:
    float m_power = 1.0f;
    float m_speed = 1.0f;

    Vec2<float> m_muzzle_position;
    Vec2<float> m_aim_position;
};