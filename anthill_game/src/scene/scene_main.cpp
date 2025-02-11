#include "scene_main.hpp"

#include "../logger/logger.hpp"

#include <iostream>

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Type::Info, "MainScene", "Init");
    }

    if (update())
    {
        float dt = window.time().getDeltaTime();

        if (window.input().button(IButtonID::Left).down())
        {
            m_player.move(-2 * dt, 0);
        }
        if (window.input().button(IButtonID::Right).down())
        {
            m_player.move(2 * dt, 0);
        }
        if (window.input().button(IButtonID::Action1).pressed())
        {
            m_player.jump();
        }

        if (window.input().button(IButtonID::DebugUp).down())
        {
            m_world_partitons[1]->move(0, -1);
        }
        if (window.input().button(IButtonID::DebugDown).down())
        {
            m_world_partitons[1]->move(0, 1);
        }
        if (window.input().button(IButtonID::DebugLeft).down())
        {
            m_world_partitons[1]->move(-1, 0);
        }
        if (window.input().button(IButtonID::DebugRight).down())
        {
            m_world_partitons[1]->move(1, 0);
        }

        if (window.input().button(IButtonID::Debug1).pressed())
        {
            reset();
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

        Vec2<int> mousePos = window.input().getMousePos();
        Vec2<int> transformed_mousePos = m_camera.transformPoint(mousePos.x, mousePos.y);
        if (window.input().button(IButtonID::Action2).down())
        {
            for (World *world : m_world_partitons)
            {
                world->drawParticles(transformed_mousePos.x, transformed_mousePos.y, 15, Particle(m_preset), World::DrawShape::Circle);
            }
        }

        Vec2<int> playerpos = m_player.getBoundingBox().getPosition();
        if (window.input().button(IButtonID::Debug7).pressed())
        {
            Vec2<int> offset = transformed_mousePos - playerpos;
            m_player.setXVelocity(offset.x / 10.0f);
            m_player.setYVelocity(offset.y / 10.0f);
        }

        BoundingBox bb(transformed_mousePos.x, transformed_mousePos.y, 100, 100);
        for (World *world : m_world_partitons)
        {
            world->update();
        }

        // m_player.update();

        m_camera.setGoal(playerpos.x, playerpos.y);
        m_camera.update(dt);

        for (World *world : m_world_partitons)
        {
            window.render().renderTexture(world->getWorldTexture(), &m_camera);

            // for (const Segment &segment : world->getWorldHitbox())
            // {
            //     window.render().debug_renderSegment(segment, Color(255, 60, 60, 255), &m_camera);
            // }
        }

        window.render().debug_renderBoundingBox(m_player.getBoundingBox(), Color(0, 255, 100, 255), &m_camera);
        window.render().debug_renderBoundingBox(bb, Color(255, 0, 0, 255), &m_camera);

        window.render().renderText(assets.fonts.alagard.font, std::to_string((int)window.time().getFramerate()), Vec2<int>(1, window.getScale() - 15), Color(0, 255, 0, 255));
        window.render().renderText(assets.fonts.alagard.font, std::to_string(window.time().getDeltaTime()), Vec2<int>(30, window.getScale() - 15), Color(255, 255, 0, 255));
        window.render().renderText(assets.fonts.alagard.font, "X: " + std::to_string(playerpos.x) + "  Y: " + std::to_string(playerpos.y), Vec2<int>(100, window.getScale() - 15), Color(255, 0, 0, 255));
    }

    return SceneID::Main;
}