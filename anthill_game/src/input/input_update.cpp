#include "input_manager.hpp"

void InputManager::update()
{
    for (auto &button : m_buttons)
    {
        button.second.update();
    }

    update_gamepad();
}