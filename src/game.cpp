#include "game.hpp"

#include <iostream>
#include <cmath>

#include "texture/texture.hpp"

#include "world/world.hpp"

#include "math/random.hpp"

#include <SDL3_ttf/SDL_ttf.h>

Game::Game() : window("ANTHILL", 512, 512, 256)
{
    World world(window.getSDLRenderer(), 256, 256);
    Camera camera;

    window.time().setTargetFramerate(144);

    Random::seed();

    Particle::Preset preset = Particle::Preset::Sand;
    while (window.isOpen())
    {
        window.time().frameStart();

        window.clear();
        window.update();

        if (window.input().isDown(Input::Up))
        {
            camera.move(0, -1);
        }
        if (window.input().isDown(Input::Down))
        {
            camera.move(0, 1);
        }
        if (window.input().isDown(Input::Left))
        {
            camera.move(-1, 0);
        }
        if (window.input().isDown(Input::Right))
        {
            camera.move(1, 0);
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

        Vec2<int> mousePos = window.input().getMousePos();
        if (window.input().isDown(Input::Action1))
        {
            Vec2<int> worldSize = world.getSize();

            Vec2<int> drawPos = camera.transformPoint(mousePos.x + worldSize.x / 2, mousePos.y + worldSize.y / 2);
            world.drawParticles(drawPos.x, drawPos.y, 5, preset);
        }

        world.update();

        const std::vector<Segment> worldBounds = world.getWorldBounds();
        window.renderTexture(world.getWorldTexture(), &camera);

        // for (const Segment &seg : worldBounds)
        // {
        //     window.debug_renderSegment(seg, 50, 255, 100, 10, &camera);
        // }

        window.renderText(std::to_string((int)window.time().getFramerate()), Vec2<int>(1, window.getScale() - 10), Color(0, 255, 0, 255));
        window.renderText(std::to_string(window.time().getDeltaTime()), Vec2<int>(30, window.getScale() - 10), Color(255, 255, 0, 255));

        window.display();

        window.time().frameEnd();
        window.time().delay();
    }
}