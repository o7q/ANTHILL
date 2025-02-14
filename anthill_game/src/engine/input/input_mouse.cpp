#include "input_manager.hpp"

#include <SDL3/SDL.h>

void InputManager::updateMouse(unsigned int window_width, unsigned int window_height, unsigned int window_scale)
{
    float x, y;
    SDL_GetMouseState(&x, &y);

    const float window_aspect = window_width / static_cast<float>(window_height);

    if (window_aspect > 1.0f)
    {
        const float scale_x = window_height / static_cast<float>(window_scale);
        const float offset_x = window_width - (window_scale * scale_x);

        m_mouse_pos.x = (x - offset_x / 2.0f) / scale_x;
        m_mouse_pos.y = y / (window_height / static_cast<float>(window_scale));
    }
    else
    {
        const float scale_y = window_width / static_cast<float>(window_scale);
        const float offset_y = window_height - (window_scale * scale_y);

        m_mouse_pos.x = x / (window_width / static_cast<float>(window_scale));
        m_mouse_pos.y = (y - offset_y / 2.0f) / scale_y;
    }
}