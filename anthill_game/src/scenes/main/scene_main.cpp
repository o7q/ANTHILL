#include "scene_main.hpp"

#include "../../logger/logger.hpp"

#include <iostream>

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Type::Info, "MainScene", "Init");
    }

    if (update())
    {
        handle_input();

        Vec2<int> playerpos = m_player.getPosition().toInt();

        Vec2<int> aim_pos;

        if (window.input().isGamepadMode())
        {

            Vec2<float> co = window.input().getJoystickPos();
            aim_pos.x = playerpos.x + co.x * 20;
            aim_pos.y = playerpos.y + co.y * 20;
        }
        else
        {
            Vec2<int> mousePos = window.input().getMousePos();
            aim_pos = m_camera.transformPoint(mousePos.x, mousePos.y);
        }

        crosshair_texture->setPosition(aim_pos.x, aim_pos.y);
        // window.render().debug_renderBoundingBox(BoundingBox(aim_pos.x, aim_pos.y, 4, 4), Color(255, 255, 30, 255), &m_camera);
        window.render().renderTexture(*crosshair_texture, &m_camera);

        if (window.input().button(IButtonID::Action2).down())
        {
            for (World *world : m_world_partitons)
            {
                world->drawParticles(aim_pos.x, aim_pos.y, 30, Particle(m_preset), World::DrawShape::Circle);
            }
        }

        if (window.input().button(IButtonID::Debug7).pressed())
        {
            Vec2<int> offset = aim_pos - playerpos;
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