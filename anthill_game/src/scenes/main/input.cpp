#include "scene_main.hpp"

void MainScene::handle_input()
{

    Vec2<float> co = window.input().getJoystickPos();

    if (window.input().button(IButtonID::Left).down() || co.x <= -0.5f)
    {
        m_player.move(-2 * DT, 0);
    }
    if (window.input().button(IButtonID::Right).down() || co.x >= 0.5f)
    {
        m_player.move(2 * DT, 0);
    }
    if (window.input().button(IButtonID::Action1).pressed())
    {
        m_player.jump();
        window.input().rumbleGamepad(30000, 30000, 100);
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