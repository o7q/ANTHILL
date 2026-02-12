#pragma once

#include "../engine/math/vector.hpp"
#include "../engine/math/bounding_box.hpp"
#include "../world/world.hpp"

class Bullet
{
public:
    Bullet(float start_x, float start_y, float target_x, float target_y);

    void update(float dt);
    bool hit() const { return m_hit; }

    bool hitWorld(World *world, float dt);
    bool hitBoundingBox(BoundingBox *bb, float dt);

    void setSpeed(float speed) { m_speed = speed; }
    void setPower(float power) { m_power = power; }

    float getPower() const { return m_power; }
    Vec2<float> getPosition() const { return m_position; }

private:
    Vec2<float> m_position;

    float m_dx = 0.0f;
    float m_dy = 0.0f;

    float m_speed = 1.0f;
    float m_power = 1.0f;

    bool m_hit = false;
};