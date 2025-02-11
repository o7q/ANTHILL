#include "input_manager.hpp"

InputManager::InputManager()
{
    init_buttons();
}
InputManager::~InputManager()
{
    for (auto &gamepad : m_gamepads)
    {
        remove_gamepad(gamepad.first);
    }
}

void InputManager::init_buttons()
{
    IButton up;
    up.assignKey(SDLK_W);
    up.assignGamepadButton(SDL_GAMEPAD_BUTTON_DPAD_UP);
    add_button(IButtonID::Up, up);

    IButton down;
    down.assignKey(SDLK_S);
    down.assignGamepadButton(SDL_GAMEPAD_BUTTON_DPAD_DOWN);
    add_button(IButtonID::Down, down);

    IButton left;
    left.assignKey(SDLK_A);
    left.assignGamepadButton(SDL_GAMEPAD_BUTTON_DPAD_LEFT);
    add_button(IButtonID::Left, left);

    IButton right;
    right.assignKey(SDLK_D);
    right.assignGamepadButton(SDL_GAMEPAD_BUTTON_DPAD_RIGHT);
    add_button(IButtonID::Right, right);

    IButton action1;
    action1.assignKey(SDLK_SPACE);
    action1.assignGamepadButton(SDL_GAMEPAD_BUTTON_SOUTH);
    add_button(IButtonID::Action1, action1);

    IButton action2;
    action2.assignMouseButton(SDL_BUTTON_LEFT);
    action2.assignGamepadButton(SDL_GAMEPAD_BUTTON_WEST);
    add_button(IButtonID::Action2, action2);

    IButton fullscreen;
    fullscreen.assignKey(SDLK_F11);
    add_button(IButtonID::Fullscreen, fullscreen);

    IButton debug1;
    debug1.assignKey(SDLK_1);
    add_button(IButtonID::Debug1, debug1);

    IButton debug2;
    debug2.assignKey(SDLK_2);
    add_button(IButtonID::Debug2, debug2);

    IButton debug3;
    debug3.assignKey(SDLK_3);
    add_button(IButtonID::Debug3, debug3);

    IButton debug4;
    debug4.assignKey(SDLK_4);
    add_button(IButtonID::Debug4, debug4);

    IButton debug5;
    debug5.assignKey(SDLK_5);
    add_button(IButtonID::Debug5, debug5);

    IButton debug6;
    debug6.assignKey(SDLK_6);
    add_button(IButtonID::Debug6, debug6);

    IButton debug7;
    debug7.assignKey(SDLK_7);
    add_button(IButtonID::Debug7, debug7);

    IButton debug8;
    debug8.assignKey(SDLK_8);
    add_button(IButtonID::Debug8, debug8);

    IButton debug9;
    debug9.assignKey(SDLK_9);
    add_button(IButtonID::Debug9, debug9);

    IButton debug0;
    debug0.assignKey(SDLK_0);
    add_button(IButtonID::Debug0, debug0);

    IButton debug_up;
    debug_up.assignKey(SDLK_UP);
    add_button(IButtonID::DebugUp, debug_up);

    IButton debug_down;
    debug_down.assignKey(SDLK_DOWN);
    add_button(IButtonID::DebugDown, debug_down);

    IButton debug_left;
    debug_left.assignKey(SDLK_LEFT);
    add_button(IButtonID::DebugLeft, debug_left);

    IButton debug_right;
    debug_right.assignKey(SDLK_RIGHT);
    add_button(IButtonID::DebugRight, debug_right);
}

void InputManager::add_button(IButtonID id, IButton button)
{
    m_buttons.insert(std::make_pair(id, button));
}