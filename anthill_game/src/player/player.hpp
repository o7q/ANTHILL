#pragma once

#include "../engine/window/window.hpp"
#include "../entity/living_entity.hpp"

#include "../weapon/shotgun/shotgun.hpp"

class Player : public LivingEntity
{
public:
    Player(Window &window, const std::vector<World *> &worlds) : LivingEntity(window, worlds)
    {
        m_bb_collider.setYSensitivity(4.0f);

        m_weapon = new Shotgun();
        m_weapon->setSpeed(30.0f);
        m_weapon->setPower(5.0f);
        m_weapon->setKnockbackPower(5.0f);
    }

    void update() override;
    void jump(bool override = false) override;
    void unjump();

private:
    void update_x_velocity() override;
    void update_y_velocity() override;

private:
    const int m_jump_buffer_height = 40;
    const float m_coyote_time = 10.0f;
    const float m_unjump_amount = 1.5f;

    const int m_extra_jumps = 1;
    int m_jumps_left = 0;
    bool m_jumped = false;

    bool m_jump_buffered = false;
    float m_coyote_time_timer = 0.0f;
};