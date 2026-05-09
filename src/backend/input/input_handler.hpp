#pragma once

#include "identifiers/input.hpp"
#include "input.hpp"
#include "math/vec.hpp"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_keycode.h>
#include <SDL3/SDL_mouse.h>
#include <optional>
#include <unordered_map>

class InputHandler
{
  public:
    InputHandler()                                     = default;
    InputHandler(const InputHandler &other)            = delete;
    InputHandler &operator=(const InputHandler &other) = delete;
    ~InputHandler()                                    = default;

    void poll(SDL_Event &event);
    void update();

    void assignInput(InputID key, const std::vector<Input::Bind> &binds);
    const std::optional<Input> getInput(InputID key);

    Vec2f getMousePosition() const { return m_mousePosition; }

  private:
    std::unordered_map<InputID, Input> m_inputs;

    Vec2f m_mousePosition;
};
