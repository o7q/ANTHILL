#include "engine/verlet.hpp"
#include "engine/window.hpp"
#include <SDL3/SDL_mouse.h>
#include <iostream>
int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(80, 40));

    window.getInputHandler().addInput(
        "draw", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    VerletController verlet;

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {

        window.frameStart();

        if (window.getInputHandler().getInput("draw")->isDown())
        {
            Vec2<unsigned int> viewport_pos = window.windowToViewportPosition(
                window.getInputHandler().getMousePosition());
            Vec2<unsigned int> pos = Vec2<unsigned int>(verlet.getPosition().x,
                                                        verlet.getPosition().y);

            Vec2<unsigned int> diff = viewport_pos - pos;

            std::cout << diff.x << " " << diff.y << std::endl;

            verlet.setAcceleration(Vec2<float>(diff.x, diff.y));
        }

        verlet.update();

        window.getViewport().setPixel(
            Vec2<unsigned int>(verlet.getPosition().x, verlet.getPosition().y),
            Color(255, 0, 0));

        window.render();
    }

    return 0;
}
