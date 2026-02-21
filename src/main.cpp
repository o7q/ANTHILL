#include "engine/color.hpp"
#include "engine/sparse_chunk_map.hpp"
#include "engine/window/window.hpp"
#include <SDL3/SDL_mouse.h>

int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(300, 200));

    window.getInputHandler().addInput(
        "click", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    SparseChunkMap<Color> map(50, 50);

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.frameStart();
        window.getViewport().clear();

        Vec2<float> mousePos = window.getInputHandler().getMousePosition();
        Vec2<unsigned int> viewportMousePos =
            window.windowToViewportPosition(mousePos);

        map.set(viewportMousePos.x, viewportMousePos.y, Color(255, 255, 255));

        for (auto &[pos, chunk] : map.getChunks())
        {
            for (int y = 0; y < map.getChunkSize().y; ++y)
            {
                for (int x = 0; x < map.getChunkSize().x; ++x)
                {
                    unsigned int sx = pos.first * map.getChunkSize().x + x;
                    unsigned int sy = pos.second * map.getChunkSize().y + y;
                    window.getViewport().setPixel(Vec2<unsigned int>(sx, sy),
                                                  map.get(sx, sy));
                }
            }
        }

        window.render();
        window.frameEnd();
    }

    return 0;
}