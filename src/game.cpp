#include "game.hpp"

#include <iostream>
#include <cmath>

#include "texture/texture.hpp"

#include "world/world.hpp"

Game::Game() : window("ANTHILL", 512, 512, 128)
{
    float fps = 60.0f;

    World world(window.getSDLRenderer(), 512, 512);

    Camera camera;

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

        Vec2<int> mousePos = window.getInput().getMousePos();
        if (window.getInput().isDown(Input::Action1))
        {
            Vec2<unsigned int> worldSize = world.getSize();

            Particle particle;
            particle.color = 0xFFFF00FF;
            Vec2<int> drawPos = camera.transformPoint(mousePos.x + worldSize.x / 2, mousePos.y + worldSize.y / 2);
            world.setParticle(drawPos.x, drawPos.y, particle);
        }

        world.update();

        window.renderTexture(world.getWorldTexture(), &camera);

        window.display();

        SDL_Delay(1000.0f / fps);
    }
}