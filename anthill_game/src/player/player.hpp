#pragma once

#include <cmath>

#include "../engine/window/window.hpp"
#include "../entity/living_entity.hpp"

#include "../weapon/shotgun/shotgun.hpp"

class Player : public LivingEntity
{
public:
    Player(Window &window, const std::vector<World *> &worlds);
    ~Player();

    void update() override;
    void jump(bool override = false) override;
    void unjump();

    void dash(float time);
    bool dashing() const { return m_dashing; }

    bool inputEnabled() const { return m_input_enabled; }

private:
    void update_x_velocity() override;
    void update_y_velocity() override;

private:
    const int m_jump_buffer_height = 40;
    const float m_coyote_time = 10.0f;
    const float m_unjump_damping = 1.5f;
    const int m_extra_jumps = 1;

private:
    bool m_jump_buffered = false;
    float m_coyote_time_timer = 0.0f;

    int m_jumps_left = 0;
    bool m_jumped = false;

    bool m_input_enabled = true;

    float m_dash_timer = 0.0f;
    bool m_dashing = false;
    Vec2<float> m_dash_vector;
};