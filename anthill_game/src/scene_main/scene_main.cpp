#include "scene_main.hpp"

#include "../engine/logger/logger.hpp"

#include <iostream>

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Type::Info, "MainScene", "Init");
        m_window.setCursor(m_assets.images.crosshair_2x.getSDLSurface());
    }

    if (update())
    {
        handle_input();

        if (m_window.input().button(IButtonID::Action2).down())
        {
            for (World *world : m_wp_manager.getWorldPartitions())
            {
                world->drawParticles(m_aim_position.x, m_aim_position.y, 30, Particle(m_preset), World::DrawShape::Circle);
            }
        }

        if (m_window.input().button(IButtonID::Debug8).pressed())
        {
            reset();
        }

        if (m_window.input().button(IButtonID::Debug9).pressed())
        {
            Vec2<float> mouse_pos = m_window.input().getMousePos();
            mouse_pos = m_camera.windowToGame(mouse_pos.x, mouse_pos.y);
            m_bullets.push_back(Bullet(mouse_pos.x, mouse_pos.y, 0, 0));
        }
        m_wp_manager.update(m_player.getPosition());

        handle_update();
        handle_render();
        handle_hud();


        for (Bullet &bullet : m_bullets)
        {
            bullet.update();
            m_window.render().debug_renderPoint(bullet.getPosition().x, bullet.getPosition().y, Color(255, 0, 0, 255), &m_camera);
        }
    }

    return SceneID::Main;
}