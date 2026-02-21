#pragma once

#include "engine/color.hpp"
#include "engine/utils.hpp"
#include <vector>
class Texture
{
  public:
    Texture(unsigned int width, unsigned int height)
    {
        m_pixels.resize(width * height);
        m_size = Vec2<unsigned int>(width, height);
    }
    Texture(const Texture &other) = delete;
    Texture &operator=(const Texture &other) = delete;

    void setPixel(unsigned int x, unsigned int y, Color color)
    {
        m_pixels[Utils::index_2dto1d(x, y, m_size.x)] = color;
    }

    Color getPixel(unsigned int x, unsigned int y) const
    {
        return m_pixels[Utils::index_2dto1d(x, y, m_size.x)];
    }

    Vec2<unsigned int> getSize() const { return m_size; }

  private:
    std::vector<Color> m_pixels;
    Vec2<unsigned int> m_size;
};
