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

    Camera camera;

    Random::seed();
    Particle particle;
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
            particle.color = Color(255, 227, 150, 255);
            particle.p_state = Particle::PState::Solid;
            particle.p_mode = Particle::PMode::Sand;
        }
        if (window.getInput().wasPressed(Input::Debug2))
        {
            particle.color = Color(31, 169, 255, 200);
            particle.p_state = Particle::PState::Liquid;
            particle.p_mode = Particle::PMode::Water;
        }

        Vec2<int> mousePos = window.getInput().getMousePos();
        if (window.getInput().isDown(Input::Action1))
        {
            Vec2<int> worldSize = world.getSize();

            Vec2<int> drawPos = camera.transformPoint(mousePos.x + worldSize.x / 2, mousePos.y + worldSize.y / 2);
            world.setParticle(drawPos.x, drawPos.y, particle);
        }

        world.update();

        window.renderTexture(texture, &camera);
        window.renderTexture(world.getWorldTexture(), &camera);

        window.display();

        SDL_Delay(1000.0f / fps);
    }
}