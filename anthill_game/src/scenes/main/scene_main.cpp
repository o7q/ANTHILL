#include "scene_main.hpp"

#include "../../logger/logger.hpp"

#include <iostream>

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Type::Info, "MainScene", "Init");
        window.setCursor(assets.images.crosshair_2x.getSDLSurface());
    }

    if (update())
    {
        handle_input();

        Vec2<float> playerpos = m_player.getPosition();
        if (window.input().isGamepadMode())
        {
            Vec2<float> joystick_pos = window.input().getJoystickPos(1);
            aim_position.x = playerpos.x + joystick_pos.x * 20;
            aim_position.y = playerpos.y + joystick_pos.y * 20;
        }
        else
        {
            Vec2<int> mousePos = window.input().getMousePos();
            aim_position = m_camera.transformPoint(mousePos.x, mousePos.y);
        }

        if (window.input().button(IButtonID::Action2).down())
        {
            for (World *world : m_world_partitons)
            {
                world->drawParticles(aim_position.x, aim_position.y, 30, Particle(m_preset), World::DrawShape::Circle);
            }
        }

        if (window.input().button(IButtonID::Debug7).pressed())
        {
            Vec2<float> offset = aim_position - playerpos;
            m_player.setXVelocity(offset.x / 10.0f);
            m_player.setYVelocity(offset.y / 10.0f);
        }
        if (window.input().button(IButtonID::Debug8).pressed())
        {
            reset();
        }

        handle_world();

        handle_update();
        handle_render();
        handle_hud();
    }

    return SceneID::Main;
}