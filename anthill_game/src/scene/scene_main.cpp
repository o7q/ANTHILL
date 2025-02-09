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
            player.move(-2 * dt, 0);
        }
        if (window.input().button(IButtonID::Right).down())
        {
            player.move(2 * dt, 0);
        }
        if (window.input().button(IButtonID::Action1).pressed())
        {
            player.jump();
        }

        if (window.input().button(IButtonID::DebugUp).down())
        {
            camera.move(0, -5 * dt);
        }
        if (window.input().button(IButtonID::DebugDown).down())
        {
            camera.move(0, 5 * dt);
        }
        if (window.input().button(IButtonID::DebugLeft).down())
        {
            camera.move(-5 * dt, 0);
        }
        if (window.input().button(IButtonID::DebugRight).down())
        {
            camera.move(5 * dt, 0);
        }

        if (window.input().button(IButtonID::Debug1).pressed())
        {
            reset();
        }
        if (window.input().button(IButtonID::Debug2).pressed())
        {
            preset = Particle::Preset::Stone;
        }
        if (window.input().button(IButtonID::Debug3).pressed())
        {
            preset = Particle::Preset::Sand;
        }
        if (window.input().button(IButtonID::Debug4).pressed())
        {
            preset = Particle::Preset::Water;
        }
        if (window.input().button(IButtonID::Debug5).pressed())
        {
            preset = Particle::Preset::Blood;
        }
        if (window.input().button(IButtonID::Debug6).pressed())
        {
            preset = Particle::Preset::Steam;
        }

        Vec2<int> mousePos = window.input().getMousePos();
        Vec2<int> transformed_mousePos = camera.transformPoint(mousePos.x, mousePos.y);
        if (window.input().button(IButtonID::Action2).down())
        {
            world.drawParticles(transformed_mousePos.x, transformed_mousePos.y, 50, preset);
        }

        Vec2<int> playerpos = player.getBoundingBox().getPosition();
        BoundingBox bb(transformed_mousePos.x, transformed_mousePos.y, 50, 50);

        if (window.input().button(IButtonID::Debug7).pressed())
        {
            Vec2<int> offset = transformed_mousePos - playerpos;
            player.setXVelocity(offset.x / 10.0f);
            player.setYVelocity(offset.y / 10.0f);
        }

        camera.setGoal(playerpos.x, playerpos.y);
        world.update(&bb);
        player.update();
        camera.update(dt);

        window.render().renderTexture(world.getWorldTexture(), &camera);
        window.render().debug_renderBoundingBox(player.getBoundingBox(), Color(0, 255, 100, 255), &camera);
        window.render().debug_renderBoundingBox(bb, Color(255, 0, 0, 255), &camera);

        window.render().renderText(assets.fonts.alagard.font, std::to_string((int)window.time().getFramerate()), Vec2<int>(1, window.getScale() - 15), Color(0, 255, 0, 255));
        window.render().renderText(assets.fonts.alagard.font, std::to_string(window.time().getDeltaTime()), Vec2<int>(30, window.getScale() - 15), Color(255, 255, 0, 255));
        window.render().renderText(assets.fonts.alagard.font, "X: " + std::to_string(playerpos.x) + "  Y: " + std::to_string(playerpos.y), Vec2<int>(100, window.getScale() - 15), Color(255, 0, 0, 255));
    }

    return SceneID::Main;
}