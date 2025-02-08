#pragma once

#include "../math/bounding_box.hpp"
#include "../math/vector.hpp"
#include "../world/world.hpp"
#include "../window/window.hpp"

#include "../collision/bounding_box_world/bb_world_collider.hpp"

class Entity
{
public:
    Entity(Window &window, const World &world) : m_window(window), m_world(world), m_bb_collider(m_bounding_box, world) {}
    virtual ~Entity() {}

    virtual void update();

    void setPosition(float x, float y);
    void move(float x, float y);
    void setXVelocity(float x);
    void setYVelocity(float y);
    void setBoundsSize(int width, int height);
    virtual void jump(bool override = false);

    void setGravityAffected(bool value);
    void setGravityStrength(float gravity);
    void setTerminalVelocity(float terminal_velocity);
    void setJumpPower(float jump_power);

    const BoundingBox &getBoundingBox() const { return m_bounding_box; }

protected:
    bool check_ground(int y_scan = 1);
    void update_x_velocity();
    void update_y_velocity();
    void resolve_world_collision();

protected:
    Window &m_window;
    const World &m_world;

    BoundingBox m_bounding_box;
    BBWorldCollider m_bb_collider;

    Vec2<float> m_position;
    Vec2<float> m_velocity;
    Vec2<int> m_bounds_size;

    // settings
protected:
    float m_terminal_velocity = 5.0f;
    float m_gravity_strength = 0.5f;
    float m_air_resistance = 1.1f;
    float m_jump_power = 8.0f;

    bool m_on_ground = false;
    bool m_is_gravity_affected = true;

private:
    void update_bounding_box();
};