#pragma once

#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <string>
#include <unordered_map>

class Input
{
  public:
    enum class ButtonType
    {
        Keyboard,
        Mouse
    };

  public:
    Input() {}

    void update()
    {
        m_pressed = m_down && !m_wasDown;
        m_unpressed = m_wasDown && !m_down;

        m_wasDown = m_down;
    }

    void assignKey(int keyCode)
    {
        m_assignedButtons[ButtonType::Keyboard] = keyCode;
    }
    void assignMouseButton(int mouseButton)
    {
        m_assignedButtons[ButtonType::Mouse] = mouseButton;
    }

    bool isDown() const { return m_down; }
    bool wasPressed() const { return m_pressed; }
    bool wasUnpressed() const { return m_unpressed; }

    bool isButtonTypeAssigned(ButtonType buttonType) const {
        
    }

  private:
    std::unordered_map<ButtonType, int> m_assignedButtons;

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

    void update(SDL_Event &event)
    {
        for (auto &input : m_inputs)
        {
            input.second.update();
        }
    }

    std::unordered_map<std::string, Input> m_inputs;
};
