#include "scene_main.hpp"

#include <iostream>

void MainScene::handle_input()
{
    if (window.input().isGamepadMode())
    {
        Vec2<float> player_pos = m_player.getPosition();
        if (window.input().joystickMoved(0) || window.input().joystickMoved(1))
        {
            Vec2<float> joystick_pos = window.input().joystickMoved(1) ? window.input().getJoystickDirection(1) : window.input().getJoystickDirection(0);

            m_aim_position_gamepad = joystick_pos * 40;
        }

        m_aim_position = player_pos + m_aim_position_gamepad;
    }
    else
    {
        Vec2<int> mouse_pos = window.input().getMousePos();
        m_aim_position = m_camera.transformPoint(mouse_pos.x, mouse_pos.y);
    }

    Vec2<float> co = window.input().getJoystickPos(0);

    if (window.input().button(IButtonID::Left).down() || co.x <= -0.5f)
    {
        m_player.move(-3 * DT, 0);
    }
    if (window.input().button(IButtonID::Right).down() || co.x >= 0.5f)
    {
        m_player.move(3 * DT, 0);
    }
    if (window.input().button(IButtonID::Action1).pressed())
    {
        m_player.jump();
    }
    if (window.input().button(IButtonID::Action1).unpressed())
    {
        m_player.unjump();
    }

    if (window.input().button(IButtonID::Fullscreen).pressed())
    {
        window.setFullscreen(!window.isFullscreen());
    }

    if (window.input().button(IButtonID::Debug1).pressed())
    {
        m_preset = Particle::Preset::Air;
    }
    if (window.input().button(IButtonID::Debug2).pressed())
    {
        m_preset = Particle::Preset::Stone;
    }
    if (window.input().button(IButtonID::Debug3).pressed())
    {
        m_preset = Particle::Preset::Sand;
    }
    if (window.input().button(IButtonID::Debug4).pressed())
    {
        m_preset = Particle::Preset::Water;
    }
    if (window.input().button(IButtonID::Debug5).pressed())
    {
        m_preset = Particle::Preset::Blood;
    }
    if (window.input().button(IButtonID::Debug6).pressed())
    {
        m_preset = Particle::Preset::Steam;
    }
}