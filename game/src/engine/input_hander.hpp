#pragma once

#include "utils.hpp"
#include "vec.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

class Input
{
  public:
    enum class ButtonType
    {
        Key,
        Mouse
    };

    struct Bind
    {
        ButtonType type;
        unsigned int id;

        bool operator==(const Bind &other) const
        {
            return type == other.type && id == other.id;
        }
    };

  public:
    Input() {}

    void poll(Bind bind, bool isDown)
    {
        if (Utils::doesVectorContain(m_binds, bind))
        {
            m_down = isDown;
        }
    }

    void update()
    {
        m_pressed = m_down && !m_wasDown;
        m_unpressed = m_wasDown && !m_down;

        m_wasDown = m_down;
    }

    void assignBind(const Bind &bind) { m_binds.push_back(bind); }
    void removeBind(const Bind &bind)
    {
        Utils::removeItemFromVector(m_binds, bind);
    }
    void removeBindsOfType(ButtonType type)
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

    bool isDown() const { return m_down; }
    bool wasDown() const { return m_wasDown; }
    bool wasPressed() const { return m_pressed; }
    bool wasUnpressed() const { return m_unpressed; }

  private:
    std::vector<Bind> m_binds;

    bool m_down = false;
    bool m_wasDown = false;
    bool m_pressed = false;
    bool m_unpressed = false;
};

class InputHandler
{
  public:
    InputHandler() = default;
    InputHandler(const InputHandler &other) = delete;
    InputHandler &operator=(const InputHandler &other) = delete;

    void poll(SDL_Event &event)
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
        }
    }

    void update()
    {
        SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);

        for (auto &inputPair : m_inputs)
        {
            inputPair.second.update();
        }
    }

    void addInput(const std::string &id, const std::vector<Input::Bind> &binds)
    {
        Input input;
        for (const Input::Bind &bind : binds)
        {
            input.assignBind(bind);
        }

        m_inputs[id] = input;
    }

    const std::optional<Input> getInput(const std::string &id)
    {
        if (m_inputs.contains(id))
        {
            return m_inputs.at(id);
        }

        return std::nullopt;
    }

    Vec2<float> getMousePosition() const { return m_mousePosition; }

  private:
    std::unordered_map<std::string, Input> m_inputs;

    Vec2<float> m_mousePosition;
};
