#include "input_handler.hpp"

void InputHandler::poll(SDL_Event &event)
{
    const auto poll_inputs = [&](Input::Bind bind, bool isDown)
    {
        for (auto &inputPair : m_inputs)
        {
            inputPair.second.poll(bind, isDown);
        }
    };

    switch (event.type)
    {
    case SDL_EVENT_KEY_DOWN:
        poll_inputs({Input::ButtonType::Key, event.key.key}, true);
        break;
    case SDL_EVENT_KEY_UP:
        poll_inputs({Input::ButtonType::Key, event.key.key}, false);
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        poll_inputs({Input::ButtonType::Mouse, event.button.button}, true);
        break;
    case SDL_EVENT_MOUSE_BUTTON_UP:
        poll_inputs({Input::ButtonType::Mouse, event.button.button}, false);
        break;
    }
}

void InputHandler::update()
{
    SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

    for (auto &inputPair : m_inputs)
    {
        inputPair.second.update();
    }
}

void InputHandler::assignInput(InputID key, const std::vector<Input::Bind> &binds)
{
    Input input;
    for (const Input::Bind &bind : binds)
    {
        input.assignBind(bind);
    }

    m_inputs[key] = input;
}

const std::optional<Input> InputHandler::getInput(InputID key)
{
    if (m_inputs.count(key))
    {
        return m_inputs.at(key);
    }

    return std::nullopt;
}
