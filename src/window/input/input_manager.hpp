#pragma once

#include <SDL3/SDL.h>

#include "../../math/vector.hpp"

enum class Input
{
    Up,
    Down,
    Left,
    Right,

    Action1,
    Action2,
    Action3,
    Action4,

    Debug1,
    Debug2,
    Debug3,
    Debug4,
    Debug5,
    Debug6
};

class InputManager
{
private:
    struct InputData
    {
        void setDown(bool down)
        {
            m_down = down;
        }

        bool isDown() const { return m_down; }

        bool wasPressed()
        {
            if (m_down && !m_pressed)
            {
                m_pressed = true;
                return true;
            }

            if (!m_down)
            {
                m_pressed = false;
            }

            return false;
        }

    private:
        bool m_down = false;
        bool m_pressed = false;
    };

public:
    void poll(SDL_Event event);

    bool isDown(Input input);
    bool wasPressed(Input input);

    void updateMouse(unsigned int window_width, unsigned int window_height, unsigned int window_scale);
    Vec2<int> getMousePos() const { return m_mouse_pos; }

    bool isController() const { return m_controller_mode; };

private:
    void handle_keydown(SDL_KeyboardEvent event);
    void handle_keyup(SDL_KeyboardEvent event);

    void handle_mousedown(SDL_MouseButtonEvent event);
    void handle_mouseup(SDL_MouseButtonEvent event);

private:
    Vec2<int> m_mouse_pos;

    bool m_controller_mode = false;

    InputData m_up;
    InputData m_down;
    InputData m_left;
    InputData m_right;

    InputData m_action1;
    InputData m_action2;
    InputData m_action3;
    InputData m_action4;

    InputData m_debug1;
    InputData m_debug2;
    InputData m_debug3;
    InputData m_debug4;
    InputData m_debug5;
    InputData m_debug6;
};