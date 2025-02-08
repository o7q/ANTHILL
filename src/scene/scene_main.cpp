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
        if (window.input().button(IButtonID::Left).down())
        {
            player.move(-2, 0);
        }
        if (window.input().button(IButtonID::Right).down())
        {
            player.move(2, 0);
        }
        if (window.input().button(IButtonID::Action1).pressed())
        {
            player.jump();
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
        if (window.input().button(IButtonID::Action2).down())
        {
            Vec2<int> drawPos = camera.transformPoint(mousePos.x, mousePos.y);
            world.drawParticles(drawPos.x, drawPos.y, 5, preset);
        }

        world.update();
        player.update();
        // player.resolveWorldCollision(world);

        window.renderTexture(world.getWorldTexture(), &camera);
        // for (const Segment &seg : world.getWorldBounds())
        //     window.debug_renderSegment(seg, 255, 50, 100, 255, &camera);
        window.debug_renderBoundingBox(player.getBoundingBox(), 0, 255, 100, 255, &camera);

        window.renderText(assets.fonts.alagard_font, std::to_string((int)window.time().getFramerate()), Vec2<int>(1, window.getScale() - 10), Color(0, 255, 0, 255));
        window.renderText(assets.fonts.alagard_font, std::to_string(window.time().getDeltaTime()), Vec2<int>(30, window.getScale() - 10), Color(255, 255, 0, 255));
    }

    return SceneID::Main;
}