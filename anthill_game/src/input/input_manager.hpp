#pragma once

#include <string>
#include <vector>
#include <unordered_map>

#include <SDL3/SDL.h>

#include "button/button.hpp"
#include "../math/vector.hpp"

enum class IButtonID
{
    Up,
    Down,
    Left,
    Right,

    Action1,
    Action2,
    Action3,
    Action4,

    Fullscreen,

    Debug1,
    Debug2,
    Debug3,
    Debug4,
    Debug5,
    Debug6,
    Debug7,
    Debug8,
    Debug9,
    Debug0,

    DebugUp,
    DebugDown,
    DebugLeft,
    DebugRight
};

class InputManager
{
public:
    InputManager();
    ~InputManager();

    void update();
    void poll(SDL_Event event);

    IButton &button(IButtonID id) { return m_buttons[id]; }

    bool isGamepadMode() const { return m_gamepad_mode; }

    void updateMouse(unsigned int window_width, unsigned int window_height, unsigned int window_scale);
    Vec2<int> getMousePos() const { return m_mouse_pos; }

    Vec2<int> getJoystickPosRaw() const { return m_gamepad_pos; }
    Vec2<float> getJoystickPos() const;

    void rumbleGamepad(Uint16 low_frequency, Uint16 high_frequency, Uint32 duration);

private:
    void assign_gamepad(int id);
    void remove_gamepad(int id, bool erase_from_map);

    void update_gamepad();
    void poll_gamepad(int value, int axis);

    std::string get_gamepad_name(SDL_Gamepad* gamepad);

    void init_buttons();

    void add_button(IButtonID id, IButton button);

private:
    Vec2<int> m_mouse_pos;
    Vec2<int> m_gamepad_pos;

    std::unordered_map<IButtonID, IButton> m_buttons;

    std::unordered_map<int, SDL_Gamepad *> m_gamepads;
    bool m_gamepad_mode = false;
    int m_active_gamepad = -1;
    const int m_gamepad_deadzone = 12000;
};