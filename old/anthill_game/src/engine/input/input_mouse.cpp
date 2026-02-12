#include "input_manager.hpp"

#include <SDL3/SDL.h>

void InputManager::updateMouse(unsigned int window_width, unsigned int window_height, unsigned int scaled_width, unsigned int scaled_height)
{
    float x, y;
    SDL_GetMouseState(&x, &y);

    // code derived from:
    // https://stackoverflow.com/q/56510595

    const float window_aspect = window_width / static_cast<float>(window_height);
    const float scaled_aspect = scaled_width / static_cast<float>(scaled_height);

    if (window_aspect >= scaled_aspect)
    {
        const float zoom_factor = window_height / static_cast<float>(scaled_height);
        const float bar_size = window_width - scaled_width * zoom_factor;

        m_mouse_pos.x = (x - bar_size / 2.0f) / zoom_factor;
        m_mouse_pos.y = y / zoom_factor;
    }
    else
    {
        const float zoom_factor = window_width / static_cast<float>(scaled_width);
        const float bar_size = window_height - scaled_height * zoom_factor;

        m_mouse_pos.x = x / zoom_factor;
        m_mouse_pos.y = (y - bar_size / 2.0f) / zoom_factor;
    }
}