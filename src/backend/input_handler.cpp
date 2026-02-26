#include "input_handler.hpp"

#include "types/vec.hpp"
#include "utils/data.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

void Input::poll(Bind bind, bool isDown)
{
    if (BackendUtils::Data::doesVectorContain(m_binds, bind))
    {
        m_down = isDown;
    }
}

void Input::update()
{
    m_pressed = m_down && !m_wasDown;
    m_unpressed = m_wasDown && !m_down;

    m_wasDown = m_down;
}

void Input::assignBind(const Bind &bind) { m_binds.push_back(bind); }
void Input::removeBind(const Bind &bind)
{
    BackendUtils::Data::removeItemFromVector(m_binds, bind);
}
void Input::removeBindsOfType(ButtonType type)
{
    for (auto it = m_binds.begin(); it != m_binds.end(); ++it)
    {
        if (it->type == type)
        {
            it = m_binds.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

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

void InputHandler::addInput(const std::string &id,
                            const std::vector<Input::Bind> &binds)
{
    Input input;
    for (const Input::Bind &bind : binds)
    {
        input.assignBind(bind);
    }

    m_inputs[id] = input;
}

const std::optional<Input> InputHandler::getInput(const std::string &id)
{
    if (m_inputs.contains(id))
    {
        return m_inputs.at(id);
    }

    return std::nullopt;
}
