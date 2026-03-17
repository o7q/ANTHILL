#pragma once

#include "math/vec.hpp"
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
    Input() = default;

    void poll(Bind bind, bool isDown);

    void update();

    void assignBind(const Bind &bind);
    void removeBind(const Bind &bind);
    void removeBindsOfType(ButtonType type);

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

    void poll(SDL_Event &event);
    void update();

    void addInput(const std::string &id, const std::vector<Input::Bind> &binds);
    const std::optional<Input> getInput(const std::string &id);

    Vec2<float> getMousePosition() const { return m_mousePosition; }

  private:
    std::unordered_map<std::string, Input> m_inputs;

    Vec2<float> m_mousePosition;
};
