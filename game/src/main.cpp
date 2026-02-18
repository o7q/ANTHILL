#include "engine/verlet.hpp"
#include "engine/window.hpp"
#include <SDL3/SDL_mouse.h>
#include <cstdint>
#include <iostream>
int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(300, 200));

    window.getInputHandler().addInput(
        "click", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    VerletController verlet;

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.frameStart();

        window.getViewport().clear();

        Vec2<float> mousepos = window.getInputHandler().getMousePosition();
        Vec2<unsigned int> mouseViewport =
        window.windowToViewportPosition(mousepos);

        Vec2<float> verletPos = verlet.getPosition();
        Vec2<unsigned int> viewportPos =
            Vec2<unsigned int>(verletPos.x, verletPos.y);

        verlet.setAcceleration(Vec2<float>((mouseViewport.x - verlet.getPosition().x) / 100, (mouseViewport.y - verlet.getPosition().y) / 100));

        std::cout << mouseViewport.x << " " << mouseViewport.y << std::endl;

        window.getViewport().setPixel(viewportPos, Color(255, 0, 0));


        verlet.update();

        window.render();

        window.frameEnd();

    }

    return 0;
}