#pragma once

#include "../engine/math/vector.hpp"
#include "../world/world.hpp"
#include "../entity/entity.hpp"
#include "../player/player.hpp"

class Bullet
{
public:
    enum class HitObjectType
    {
        World,
        Entity,
        Player
    };

public:
    Bullet(float start_x, float start_y, float target_x, float target_y);

    void update(float dt);
    bool hit() const;

    void *getHitObject() const { return m_hit_object; }
    HitObjectType getHitObjectType() const { return m_hit_object_type; }

    void checkWorld(World *world, float dt);

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

    void *m_hit_object = nullptr;
    HitObjectType m_hit_object_type;
};