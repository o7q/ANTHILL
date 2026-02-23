#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/sparse_chunk_map.hpp"
#include "engine/utils/math.hpp"
#include "engine/window/window.hpp"
#include "world/particle.hpp"
#include "world/world.hpp"
#include <SDL3/SDL_mouse.h>
#include <iostream>

int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(600, 600));

    window.getInputHandler().addInput("1", {{Input::ButtonType::Key, SDLK_1}});
    window.getInputHandler().addInput("2", {{Input::ButtonType::Key, SDLK_2}});
    window.getInputHandler().addInput("3", {{Input::ButtonType::Key, SDLK_3}});
    window.getInputHandler().addInput("4", {{Input::ButtonType::Key, SDLK_4}});
    window.getInputHandler().addInput("slowmoDown",
                                      {{Input::ButtonType::Key, SDLK_Z}});
    window.getInputHandler().addInput("slowmoUp",
                                      {{Input::ButtonType::Key, SDLK_X}});
    window.getInputHandler().addInput(
        "m1", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    World world;
    Camera camera;

    std::vector<Vec2<int>> points;

    float time_multiplier = 1.0f;

    window.getTimeHandler().setTargetFramerate(144);

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.frameStart();
        window.getViewport().clear();

        Vec2<float> mousePos = window.getInputHandler().getMousePosition();
        auto viewportMousePos = window.windowToViewportPosition(mousePos);

        if (window.getInputHandler().getInput("1")->isDown())
        {
            if (viewportMousePos.has_value())
            {
                Vec2<unsigned int> pos = viewportMousePos.value();

                Particle stone;
                stone.setColor(Color(200, 200, 200));
                stone.setPhysicsType(Particle::PhysicsType::None);
                stone.setMatterType(Particle::MatterType::Solid);

                world.getParticleHandler().draw(pos.x, pos.y, stone, 20);
            }
        }
        if (window.getInputHandler().getInput("2")->isDown())
        {
            if (viewportMousePos.has_value())
            {
                Vec2<unsigned int> pos = viewportMousePos.value();

                Particle air;

                world.getParticleHandler().draw(pos.x, pos.y, air, 10);
            }
        }
        if (window.getInputHandler().getInput("3")->isDown())
        {
            if (viewportMousePos.has_value())
            {
                Vec2<unsigned int> pos = viewportMousePos.value();

                Particle sand;
                sand.setColor(Color(200, 200, 0));
                sand.setPhysicsType(Particle::PhysicsType::Sand);
                sand.setMatterType(Particle::MatterType::Solid);
                sand.getVerlet().setRestitution(0.01f);

                world.getParticleHandler().draw(pos.x, pos.y, sand, 10);
            }
        }
        if (window.getInputHandler().getInput("4")->isDown())
        {
            if (viewportMousePos.has_value())
            {
                Vec2<unsigned int> pos = viewportMousePos.value();

                Particle water;
                water.setColor(Color(50, 50, 200));
                water.setPhysicsType(Particle::PhysicsType::Water);
                water.setMatterType(Particle::MatterType::Liquid);
                water.getVerlet().setRestitution(0.05f);

                world.getParticleHandler().draw(pos.x, pos.y, water, 10);
            }
        }

        if (window.getInputHandler().getInput("m1")->isDown())
        {
            if (viewportMousePos.has_value())
            {
                Vec2<unsigned int> pos = viewportMousePos.value();
                world.getParticleHandler().applyForce(pos.x, pos.y, 3.0f);
            }
        }

        if (window.getInputHandler().getInput("slowmoDown")->wasPressed())
        {
            time_multiplier -= 0.1f;
            window.getTimeHandler().setSpeedMultiplier(time_multiplier);
        }

        if (window.getInputHandler().getInput("slowmoUp")->wasPressed())
        {
            time_multiplier += 0.1f;
            window.getTimeHandler().setSpeedMultiplier(time_multiplier);
        }

        for (int i = 0; i < 2; ++i)
        {
            world.getParticleHandler().update(
                window.getTimeHandler().getDeltaTime());
        }

        world.render(camera, window.getViewport());


        window.render();
        window.frameEnd();
    }

    return 0;
}