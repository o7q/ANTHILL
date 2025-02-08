#pragma once

#include <SDL3/SDL.h>

struct IButton
{
    enum class PollType
    {
        Keyboard,
        Controller,
        Mouse
    };

    IButton() = default;

    void assignKey(int keycode);
    void unassignKey();

    void assignGamepadButton(int gamepad_button);
    void unassignGamepadButton();

    void assignMouseButton(int mouse_button);
    void unassignMouseButton();

    void update();

    bool down() const { return m_down; }
    bool pressed() const { return m_pressed; }
    bool unpressed() const { return m_unpressed; }

    void poll(int generic_button, PollType poll_type, bool down);

private:
    bool m_down = false;
    bool m_wasDown = false;

    bool m_pressed = false;
    bool m_unpressed = false;

    int m_keycode = SDLK_UNKNOWN;
    int m_gamepad_button = SDL_GAMEPAD_BUTTON_INVALID;
    int m_mouse_button = -1;

    bool m_key_assigned = false;
    bool m_gamepad_button_assigned = false;
    bool m_mouse_button_assigned = false;
};