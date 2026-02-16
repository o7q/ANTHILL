#include "engine/window.hpp"
#include <cstdint>
#include <iostream>
int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(30, 20));

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.frameStart();

        for (int y = 0; y < window.getViewport().getSize().y; ++y)
        {
            for (int x = 0; x < window.getViewport().getSize().x; ++x)
            {
                Color col =
                    window.getViewport().getPixel(Vec2<unsigned int>(x, y));
                col.r /= 1.01f;
                col.g /= 1.1f;
                col.b /= 1.1f;
                window.getViewport().setPixel(Vec2<unsigned int>(x, y), col);
            }
        }

        Vec2<unsigned int> viewport_pos = window.windowToViewportPosition(
            window.getInputHandler().getMousePosition());

        window.getViewport().setPixel(
            Vec2<unsigned int>(viewport_pos.x, viewport_pos.y),
            Color(255, 255, 255));

        window.render();
    }

    return 0;
}