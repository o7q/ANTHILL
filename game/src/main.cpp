#include "engine/verlet.hpp"
#include "engine/window.hpp"
#include <SDL3/SDL_mouse.h>
#include <cstdint>
#include <iostream>
int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(30, 20));

    window.getInputHandler().addInput(
        "click", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    VerletController verlet;

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.frameStart();

        // verlet.setAcceleration(Vec2<float>(0, 0.00001));

        // window.getViewport().clear();

        // // Vec2<float> mousepos = window.getInputHandler().getMousePosition();
        // // Vec2<unsigned int> viewportPos =
        // // window.windowToViewportPosition(mousepos);

        // Vec2<float> verletPos = verlet.getPosition();
        // Vec2<unsigned int> viewportPos =
        //     Vec2<unsigned int>(verletPos.x, verletPos.y);

        // window.getViewport().setPixel(viewportPos, Color(255, 0, 0));

        // std::cout << verletPos.x << " " << verletPos.y << std::endl;

        // verlet.update();

        window.render();

        std::cout << window.getTimeHandler().getFramerate() << std::endl;

        window.frameEnd();

    }

    return 0;
}