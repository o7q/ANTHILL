#pragma once

#include <string>

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "input/input_manager.hpp"
#include "time/time_manager.hpp"

#include "../camera/camera.hpp"
#include "../math/vector.hpp"

#include "../texture/texture.hpp"
#include "../math/bounding_box.hpp"
#include "../math/segment.hpp"
#include "../math/color.hpp"

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

    InputManager &input() { return m_input_manager; }
    TimeManager &time() { return m_time_manager; }
    SDL_Renderer *getSDLRenderer() const { return m_renderer; }

public:
    // rendering
    void renderTexture(const Texture &texture, const Camera *camera = nullptr);
    void renderText(TTF_Font *font, const std::string &text, Vec2<int> position, Color color, Camera *camera = nullptr);
    void debug_renderBoundingBox(const BoundingBox &boundingBox, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const Camera *camera = nullptr);
    void debug_renderSegment(const Segment &segment, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const Camera *camera = nullptr);
    void debug_renderPoint(int x, int y, Uint8 r, Uint8 g, Uint8 b, Uint8 a, const Camera *camera = nullptr);
    //

private:
    SDL_Window *m_window = nullptr;
    SDL_Renderer *m_renderer = nullptr;

    InputManager m_input_manager;
    TimeManager m_time_manager;

private:
    Vec2<int> m_window_size;
    unsigned int m_scale = 64;

    bool m_closed = false;
};