#pragma once

#include <string>

#include <SDL3/SDL.h>

#include "../math/vector.hpp"
#include "../render/render_manager.hpp"
#include "../input/input_manager.hpp"
#include "../time/time_manager.hpp"

class Window
{
public:
    Window(const std::string &title, unsigned int width, unsigned int height, unsigned int scaled_size = 64);
    ~Window();

    void update();

    void start();
    void end();

    bool isOpen() const { return !m_closed; }

    Vec2<int> getSize() const { return m_window_size; }
    unsigned int getScale() const { return m_scale; }

    RenderManager &render() { return m_render_manager; }
    InputManager &input() { return m_input_manager; }
    TimeManager &time() { return m_time_manager; }

    void setFullscreen(bool value);
    bool isFullscreen() const { return m_is_fullscreen; }

    void showCursor(bool value);
    void setCursor(SDL_Surface *cursor_surface);
    void clearCursorImage();
    bool isCursorVisible() const { return m_cursor_visible; }

    SDL_Renderer *getSDLRenderer() const { return m_renderer; }

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;
    SDL_Cursor *m_cursor = nullptr;

    RenderManager m_render_manager;
    InputManager m_input_manager;
    TimeManager m_time_manager;

private:
    Vec2<int> m_window_size;
    unsigned int m_scale = 64;

    bool m_closed = false;
    bool m_is_fullscreen = false;
    bool m_cursor_visible = true;
};