#pragma once

#include "../entity/entity.hpp"

#include "../engine/window/window.hpp"

class Player : public Entity
{
public:
    Player(Window &window, const std::vector<World *> &world_partitions) : Entity(window, world_partitions)
    {
        m_bb_collider.setYSensitivity(4.0f);
    }

    void update() override;
    void jump(bool override = false) override;
    void unjump();

private:
    const int m_jump_buffer_height = 40;
    const int m_coyote_time = 10;
    const float m_unjump_amount = 1.5f;

    bool m_jump_buffered = false;
    float m_coyote_time_timer = 0.0f;
};