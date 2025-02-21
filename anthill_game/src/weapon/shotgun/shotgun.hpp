#pragma once

#include <cmath>

#include "../../engine/math/angle.hpp"
#include "../../bullet/bullet.hpp"
#include "../weapon.hpp"

class Shotgun : public Weapon
{
    virtual ~Shotgun() {}

    virtual ShootData shoot() const override;

protected:
    float m_spread = 15.0f;
    int m_bullet_count = 10;
};