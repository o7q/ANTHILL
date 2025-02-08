#pragma once

#include "../entity/entity.hpp"
#include "../window/window.hpp"

class Player : public Entity
{
public:
    Player(Window &window, const World &world) : Entity(window, world)
    {
        m_bb_collider.setYSensitivity(4.0f);
    }

    void update() override;
    void jump(bool override = false) override;

private:
    bool m_jump_buffered = false;
    const int m_jump_buffer_height = 40;
    const int m_coyote_time = 10;
    float m_coyote_time_timer = 0.0f;
};