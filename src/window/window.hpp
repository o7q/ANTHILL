#pragma once

#include <string>

#include <SDL3/SDL.h>

#include "input/input_manager.hpp"

#include "../texture/texture.hpp"
#include "../types.hpp"

#include "../camera/camera.hpp"

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

    InputManager &getInput() { return m_input_manager; }
    SDL_Renderer *getSDLRenderer() const { return m_renderer; }

public:
    // rendering
    void renderTexture(const Texture &texture, const Camera *camera = nullptr);
    //

public:
    // global to local pos
    Vec2<int> windowToGamePos(float x, float y, const Camera *camera = nullptr) const;
    //

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    InputManager m_input_manager;

private:
    Vec2<int> m_window_size;
    unsigned int m_scale = 64;

    bool m_closed = false;
};