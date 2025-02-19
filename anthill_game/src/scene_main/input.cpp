#include "scene_main.hpp"

#include <iostream>

void MainScene::update_input()
{
    if (m_window.input().isGamepadMode())
    {
        Vec2<float> player_pos = m_player.getPosition();
        if (m_window.input().joystickMoved(0) || m_window.input().joystickMoved(1))
        {
            Vec2<float> joystick_pos = m_window.input().joystickMoved(1) ? m_window.input().getJoystickDirection(1) : m_window.input().getJoystickDirection(0);

            m_aim_position_gamepad = joystick_pos * 40;
        }

        Vec2<float> aim_position = player_pos + m_aim_position_gamepad;
        m_player.setAimPosition(aim_position.x, aim_position.y);
    }
    else
    {
        Vec2<float> mouse_pos = m_window.input().getMousePos();
        Vec2<float> aim_position = m_camera.windowToGame(mouse_pos.x, mouse_pos.y);
        m_player.setAimPosition(aim_position.x, aim_position.y);
    }

    Vec2<float> joystick_pos = m_window.input().getJoystickPos(0);

    if (m_window.input().button(IButtonID::Left).down() || joystick_pos.x <= -0.5f)
    {
        m_player.move(-3 * DT, 0);
    }
    if (m_window.input().button(IButtonID::Right).down() || joystick_pos.x >= 0.5f)
    {
        m_player.move(3 * DT, 0);
    }
    if (m_window.input().button(IButtonID::Jump).pressed())
    {
        m_player.jump();
    }
    if (m_window.input().button(IButtonID::Jump).unpressed())
    {
        m_player.unjump();
    }

    if (m_window.input().button(IButtonID::Debug1).pressed())
    {
        m_world_manager.queue(WorldGenerator::Settings(2000, 2000, -1, WorldGenerator::Settings::Preset::Jungle));
    }
    if (m_window.input().button(IButtonID::Debug2).down())
    {
        m_world_manager.purge();
    }

    m_world_manager.updateQueue();

    if (m_window.input().button(IButtonID::Shoot).pressed())
    {
        const Weapon *weapon = m_player.getWeapon();
        if (weapon != nullptr)
        {
            const std::vector<Vec2<float>> positions = weapon->shoot();

            for (Vec2<float> pos : positions)
            {
                Bullet bullet(weapon->getMuzzlePosition().x, weapon->getMuzzlePosition().y, pos.x, pos.y);
                bullet.setSpeed(weapon->getSpeed());
                bullet.setPower(weapon->getPower());
                m_bullet_manager.add(bullet);
                std::cout << weapon->getMuzzlePosition().x << " " <<  weapon->getMuzzlePosition().y << " " << pos.x << " " << pos.y << std::endl;
            }


            if (m_window.input().isGamepadMode())
            {
                m_window.input().rumbleGamepad(20000, 40000, 200);
            }
        }
    }

    if (m_window.input().button(IButtonID::Fullscreen).pressed())
    {
        m_window.setFullscreen(!m_window.isFullscreen());
    }
}