#pragma once

#include <string>

#include <SDL3/SDL.h>

#include "../render/render_manager.hpp"
#include "../input/input_manager.hpp"
#include "../time/time_manager.hpp"

#include "../camera/camera.hpp"
#include "../math/vector.hpp"

#include "../texture/texture.hpp"
#include "../math/bounding_box.hpp"
#include "../math/segment.hpp"

class Window
{
public:
    Window(const std::string &title, unsigned int width, unsigned int height, unsigned int scaled_size = 64);
    ~Window();

    void update();

    void clear();
    void display();

    bool isOpen() const { return !m_closed; }

    Vec2<int> getSize() const { return m_window_size; }
    unsigned int getScale() const { return m_scale; }

    RenderManager &render() { return m_render_manager; }
    InputManager &input() { return m_input_manager; }
    TimeManager &time() { return m_time_manager; }
	
    SDL_Renderer *getSDLRenderer() const { return m_renderer; }

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    RenderManager m_render_manager;
    InputManager m_input_manager;
    TimeManager m_time_manager;

private:
    Vec2<int> m_window_size;
    unsigned int m_scale = 64;

    bool m_closed = false;
};