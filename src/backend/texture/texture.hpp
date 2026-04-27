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
    Texture(Vec2u size);
    Texture(const std::vector<Color> &pixels, Vec2u size);
    Texture(const std::filesystem::path &path);
    Texture(const Texture &other) = default;
    Texture &operator=(const Texture &other) = default;
    ~Texture() = default;

    Vec2u getSize() const { return m_size; }

    void setPixel(Vec2u pos, Color color);
    Color getPixel(Vec2u pos) const;

    const std::vector<Color> &getPixels() const { return m_pixels; }

    void clear();

  private:
    void initNull();

  private:
    Vec2u m_size;
    std::vector<Color> m_pixels;
};
