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

        Vec2<int> mousePos = window.input().getMousePos();
        Vec2<int> transformed_mousePos = m_camera.transformPoint(mousePos.x, mousePos.y);
        if (window.input().button(IButtonID::Action2).down())
        {
            for (World *world : m_world_partitons)
            {
                world->drawParticles(transformed_mousePos.x, transformed_mousePos.y, 50, Particle(m_preset), World::DrawShape::Circle);
            }
        }

        Vec2<int> playerpos = m_player.getBoundingBox().getPosition();
        if (window.input().button(IButtonID::Debug7).pressed())
        {
            Vec2<int> offset = transformed_mousePos - playerpos;
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