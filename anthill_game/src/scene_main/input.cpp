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

            m_last_aim_position_gamepad = joystick_pos * 40;
        }

        Vec2<float> aim_position = player_pos + m_last_aim_position_gamepad;
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
        if (m_player.isAlive() && m_player.inputEnabled())
        {
            m_player.move(-3 * DT, 0);
        }
    }
    if (m_window.input().button(IButtonID::Right).down() || joystick_pos.x >= 0.5f)
    {
        if (m_player.isAlive() && m_player.inputEnabled())
        {
            m_player.move(3 * DT, 0);
        }
    }
    if (m_window.input().button(IButtonID::Jump).pressed())
    {
        if (m_player.isAlive() && m_player.inputEnabled())
        {
            m_player.jump();
        }
    }
    if (m_window.input().button(IButtonID::Jump).unpressed())
    {
        if (m_player.isAlive() && m_player.inputEnabled())
        {
            m_player.unjump();
        }
    }

    if (m_window.input().button(IButtonID::Dash).pressed())
    {
        m_player.dash(4.0f);
        if (m_window.input().isGamepadMode())
        {
            m_window.input().rumbleGamepad(30000, 20000, 300);
        }
    }

    if (m_window.input().button(IButtonID::Debug1).pressed())
    {
        m_window.time().setSpeed(1.0f);
    }
    if (m_window.input().button(IButtonID::Debug2).pressed())
    {
        m_window.time().setSpeed(0.5f);
    }
    if (m_window.input().button(IButtonID::Debug3).pressed())
    {
        m_window.time().setSpeed(0.25f);
    }
    if (m_window.input().button(IButtonID::Debug4).pressed())
    {
        m_window.time().setSpeed(0.1f);
    }
    if (m_window.input().button(IButtonID::Debug5).pressed())
    {
        m_window.time().setSpeed(0.05f);
    }
    if (m_window.input().button(IButtonID::Debug6).pressed())
    {
        m_window.time().setSpeed(2.0f);
    }
    if (m_window.input().button(IButtonID::Debug7).down())
    {
        for (World* world : m_world_manager.getWorlds())
        {
            world->drawParticles(m_player.getAimPosition().x, m_player.getAimPosition().y, 20, Particle(Particle::Preset::Water), World::DrawShape::Circle, true);
        }
    }

    if (m_window.input().button(IButtonID::Shoot).pressed())
    {
        Weapon *weapon = m_player.getWeapon();
        if (weapon != nullptr && m_player.isAlive() && m_player.inputEnabled())
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