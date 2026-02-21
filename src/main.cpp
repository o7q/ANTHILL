#include "engine/camera.hpp"
#include "engine/color.hpp"
#include "engine/sparse_chunk_map.hpp"
#include "engine/window/window.hpp"
#include "world/particle.hpp"
#include "world/world.hpp"
#include <SDL3/SDL_mouse.h>

int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(300, 200));

    window.getInputHandler().addInput("1", {{Input::ButtonType::Key, SDLK_1}});
    window.getInputHandler().addInput("2", {{Input::ButtonType::Key, SDLK_2}});
    window.getInputHandler().addInput(
        "m1", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    Camera camera;

    World world;

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.frameStart();
        window.getViewport().clear();

        Vec2<float> mousePos = window.getInputHandler().getMousePosition();
        Vec2<unsigned int> viewportMousePos =
            window.windowToViewportPosition(mousePos);

        if (window.getInputHandler().getInput("1")->isDown())
        {
            Particle p;
            p.setMatterType(Particle::MatterType::Solid);
            p.setPhysicsType(Particle::PhysicsType::None);
            p.setColor(Color(150, 150, 150));
            world.getParticleHandler().getParticles().set(
                viewportMousePos.x, viewportMousePos.y, p);
        }
        if (window.getInputHandler().getInput("2")->isDown())
        {
            Particle p;
            p.setMatterType(Particle::MatterType::Solid);
            p.setPhysicsType(Particle::PhysicsType::Sand);
            p.setColor(Color(150, 150, 80));
            world.getParticleHandler().getParticles().set(
                viewportMousePos.x, viewportMousePos.y, p);
        }
        if (window.getInputHandler().getInput("m1")->wasPressed())
        {
            world.getParticleHandler().applyForce(viewportMousePos.x, viewportMousePos.y, 1.0f);
        }

        world.getParticleHandler().update(
            window.getTimeHandler().getDeltaTime());
        world.render(camera, window.getViewport());

        window.render();
        window.frameEnd();
    }

    return 0;
}