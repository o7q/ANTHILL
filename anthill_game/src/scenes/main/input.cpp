#include "scene_main.hpp"

void MainScene::handle_input()
{
    if (window.input().button(IButtonID::Left).down())
    {
        m_player.move(-2 * DT, 0);
    }
    if (window.input().button(IButtonID::Right).down())
    {
        m_player.move(2 * DT, 0);
    }
    if (window.input().button(IButtonID::Action1).pressed())
    {
        m_player.jump();
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