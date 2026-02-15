#include "engine/window.hpp"
#include <iostream>
int main()
{
    Window window(Vec2<uint16_t>(640, 480));

    std::vector<Input::Bind> binds;
    window.getInputHandler().addInput("test",
                                      {{Input::ButtonType::Key, SDLK_W}});

    while (!window.getEventHandler().didEventOccur(
        EventHandler::EventType::WINDOW_QUIT))
    {
        window.update();

        auto input = window.getInputHandler().getInput("test");
        if (input.has_value())
        {
            // if (input->isDown())
            // {
            //     std::cout << "down!" << std::endl;
            // }

            if (input->wasPressed())
            {
                std::cout << "pressed!" << std::endl;
            }
            if (input->wasUnpressed())
            {
                std::cout << "unpressed!" << std::endl;
            }
        }
    }

    return 0;
}
