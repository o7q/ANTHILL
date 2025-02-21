#include "scene_main.hpp"

#include "../weapon/weapon.hpp"

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
        m_player.getWeapon()->setAimPosition(aim_position.x, aim_position.y);
    }
    else
    {
        Vec2<float> mouse_pos = m_window.input().getMousePos();
        Vec2<float> aim_position = m_camera.windowToGame(mouse_pos.x, mouse_pos.y);
        m_player.getWeapon()->setAimPosition(aim_position.x, aim_position.y);
    }

    Vec2<float> joystick_pos = m_window.input().getJoystickPos(0);
    if (m_window.input().button(IButtonID::Left).down() || joystick_pos.x <= -0.5f)
    {
        if (m_player.isAlive())
        {
            m_player.move(-3 * DT, 0);
        }
    }
    if (m_window.input().button(IButtonID::Right).down() || joystick_pos.x >= 0.5f)
    {
        if (m_player.isAlive())
        {
            m_player.move(3 * DT, 0);
        }
    }
    if (m_window.input().button(IButtonID::Jump).pressed())
    {
        if (m_player.isAlive())
        {
            m_player.jump();
        }
    }
    if (m_window.input().button(IButtonID::Jump).unpressed())
    {
        if (m_player.isAlive())
        {
            m_player.unjump();
        }
    }

    if (m_window.input().button(IButtonID::Debug1).pressed())
    {
        m_world_manager.queue(WorldGenerator::Settings(2000, 2000, -1, WorldGenerator::Settings::Preset::Jungle));
    }
    if (m_window.input().button(IButtonID::Debug2).pressed())
    {
        m_world_manager.purge();
    }
    if (m_window.input().button(IButtonID::Debug3).pressed())
    {
        m_player.kill();
    }

    if (m_window.input().button(IButtonID::Shoot).pressed())
    {
        Weapon *weapon = m_player.getWeapon();
        if (weapon != nullptr && m_player.isAlive())
        {
            Weapon::ShootData shoot_data = weapon->shoot();

            m_bullet_manager.addBulletRange(shoot_data.bullets);

            if (m_player.onGround())
            {
                shoot_data.knockback_vector = shoot_data.knockback_vector * 0.5f;
            }

            m_player.setXVelocity(shoot_data.knockback_vector.x);
            m_player.setYVelocity(shoot_data.knockback_vector.y);

            if (m_window.input().isGamepadMode())
            {
                m_window.input().rumbleGamepad(20000, 40000, 200);
            }
        }
    }
}