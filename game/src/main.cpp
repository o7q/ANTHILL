#include "engine/sparse_chunk_map.hpp"
#include "engine/verlet.hpp"
#include "engine/window.hpp"
#include <SDL3/SDL_mouse.h>
#include <iostream>

int main()
{
    Window window(Vec2<unsigned int>(640, 480), Vec2<unsigned int>(300, 200));

    window.getInputHandler().addInput(
        "click", {{Input::ButtonType::Mouse, SDL_BUTTON_LEFT}});

    SparseChunkMap<std::string, 2, 2> map;

    map.set(-2, -2, "55");

    // while (!window.getEventHandler().didEventOccur(
    //     EventHandler::EventType::WINDOW_QUIT))
    // {
    //     window.frameStart();
    //     window.getViewport().clear();

    //     window.render();
    //     window.frameEnd();
    // }

    return 0;
}