#pragma once

#include "math/color.hpp"
#include "math/vec.hpp"
#include <filesystem>
#include <stb/stb_image.h>
#include <vector>

class Texture
{
  public:
    Texture();
    Texture(unsigned int width, unsigned int height);
    Texture(const std::vector<Color> &pixels, unsigned int width,
            unsigned int height)
    {
        m_pixels.resize(pixels.size());
        for (unsigned int i = 0; i < pixels.size(); ++i)
        {
            m_pixels[i] = pixels[i];
        }

        m_size = Vec2u(width, height);
    }
    Texture(const std::filesystem::path &path);
    Texture(const Texture &other) = default;
    Texture &operator=(const Texture &other) = default;
    ~Texture() = default;

    Vec2u getSize() const { return m_size; }

    Color getPixel(unsigned int x, unsigned int y) const;

    const std::vector<Color> &getPixels() const { return m_pixels; }

  private:
    void initNull();

  private:
    Vec2u m_size;
    std::vector<Color> m_pixels;
};
