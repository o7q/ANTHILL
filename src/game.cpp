#include "game.hpp"

#include <iostream>
#include <cmath>

#include "texture/texture.hpp"

#include "world/world.hpp"

#include "math/random.hpp"

Game::Game() : window("ANTHILL", 512, 512, 128)
{
    float fps = 120.0f;

    World world(window.getSDLRenderer(), 128, 128);

    Texture texture(window.getSDLRenderer(), "test.png");

    BoundingBox bb(0, 0, 50, 50);

    Camera camera;

    Random::seed();
    Particle::Preset preset = Particle::Preset::Sand;
    while (window.isOpen())
    {
        window.clear();
        window.update();

        if (window.getInput().isDown(Input::Up))
        {
            camera.move(0, -1);
        }
        if (window.getInput().isDown(Input::Down))
        {
            camera.move(0, 1);
        }
        if (window.getInput().isDown(Input::Left))
        {
            camera.move(-1, 0);
        }
        if (window.getInput().isDown(Input::Right))
        {
            camera.move(1, 0);
        }

        if (window.getInput().wasPressed(Input::Debug1))
        {
            preset = Particle::Preset::Sand;
        }
        if (window.getInput().wasPressed(Input::Debug2))
        {
            preset = Particle::Preset::Water;
        }
        if (window.getInput().wasPressed(Input::Debug3))
        {
            preset = Particle::Preset::Blood;
        }

        Vec2<int> mousePos = window.getInput().getMousePos();
        if (window.getInput().isDown(Input::Action1))
        {
            Vec2<int> worldSize = world.getSize();

            Vec2<int> drawPos = camera.transformPoint(mousePos.x + worldSize.x / 2, mousePos.y + worldSize.y / 2);
            world.drawParticles(drawPos.x, drawPos.y, 5, preset);
        }

        world.update();

        window.renderTexture(texture, &camera);
        window.renderTexture(world.getWorldTexture(), &camera);

        window.debug_renderBoundingBox(bb, 0, 255, 255, 255, &camera);

        window.display();

        SDL_Delay(1000.0f / fps);
    }
}