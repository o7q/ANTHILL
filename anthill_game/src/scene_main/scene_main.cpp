#include "scene_main.hpp"

#include "../engine/logger/logger.hpp"

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

        if (window.input().button(IButtonID::Action2).down())
        {
            for (World *world : m_world_partitons)
            {
                world->drawParticles(m_aim_position.x, m_aim_position.y, 30, Particle(m_preset), World::DrawShape::Circle);
            }
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