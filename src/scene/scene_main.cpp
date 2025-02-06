#include "scene_main.hpp"

#include <iostream>

SceneID MainScene::run()
{
    if (init())
    {
        std::cout << "MainScene init" << std::endl;
    }

    if (update())
    {
        if (window.input().isDown(Input::Left))
        {
            player.move(-2, 0);
        }
        if (window.input().isDown(Input::Right))
        {
            player.move(2, 0);
        }
        if (window.input().isDown(Input::Action2))
        {
            player.jump();
        }

        if (window.input().wasPressed(Input::Debug1))
        {
            preset = Particle::Preset::Stone;
        }
        if (window.input().wasPressed(Input::Debug2))
        {
            preset = Particle::Preset::Sand;
        }
        if (window.input().wasPressed(Input::Debug3))
        {
            preset = Particle::Preset::Water;
        }
        if (window.input().wasPressed(Input::Debug4))
        {
            preset = Particle::Preset::Blood;
        }
        if (window.input().wasPressed(Input::Debug5))
        {
            preset = Particle::Preset::Steam;
        }
        if (window.input().wasPressed(Input::Debug6))
        {
            reset();
        }

        Vec2<int> mousePos = window.input().getMousePos();
        if (window.input().isDown(Input::Action1))
        {
            Vec2<int> drawPos = camera.transformPoint(mousePos.x, mousePos.y);
            world.drawParticles(drawPos.x, drawPos.y, 5, preset);
        }

        world.update();
        player.update();
        player.resolveWorldCollision(world);

        window.renderTexture(world.getWorldTexture(), &camera);
        // for (const Segment &seg : world.getWorldBounds())
        //     window.debug_renderSegment(seg, 255, 50, 100, 255, &camera);
        window.debug_renderBoundingBox(player.getBoundingBox(), 0, 255, 100, 255, &camera);

        window.renderText(assets.fonts.alagard_font, std::to_string((int)window.time().getFramerate()), Vec2<int>(1, window.getScale() - 10), Color(0, 255, 0, 255));
        window.renderText(assets.fonts.alagard_font, std::to_string(window.time().getDeltaTime()), Vec2<int>(30, window.getScale() - 10), Color(255, 255, 0, 255));
    }

    return SceneID::Main;
}