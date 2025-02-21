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

    virtual ShootData shoot() const;

    void setMuzzlePosition(float x, float y);
    void setAimPosition(float x, float y);
    void setSpeed(float speed);
    void setPower(float power);
    void setKnockbackPower(float knockback_power);

    Vec2<float> getAimPosition() const { return m_aim_position; }

protected:
    float m_speed = 30.0f;
    float m_power = 5.0f;
    float m_knockback_power = 5.0f;

    Vec2<float> m_muzzle_position;
    Vec2<float> m_aim_position;
};