#include "engine/color.hpp"
#include "engine/sparse_chunk_map.hpp"
#include "engine/window.hpp"
#include <SDL3/SDL_mouse.h>

int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(300, 200));

    window.getInputHandler().addInput(
        "click", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    SparseChunkMap<Color, 32, 32> map;

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.frameStart();
        window.getViewport().clear();

        Vec2<float> mousePos = window.getInputHandler().getMousePosition();
        Vec2<unsigned int> viewportMousePos =
            window.windowToViewportPosition(mousePos);

        map.set(viewportMousePos.x, viewportMousePos.y, Color(255, 255, 255));

        for (auto &chunkPair : map.getChunks())
        {
            SparseChunkMap<Color, 32, 32>::Chunk chunk = chunkPair.second;

            for (int y = 0; y < 32; ++y)
            {
                for (int x = 0; x < 32; ++x)
                {
                    unsigned int sx = chunkPair.first.first * 32 + x;
                    unsigned int sy = chunkPair.first.second * 32 + y;
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