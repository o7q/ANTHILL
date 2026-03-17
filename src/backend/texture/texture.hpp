#pragma once

#include "backend/logger/logger.hpp"
#include "math/color.hpp"
#include "math/index.hpp"
#include "math/vec.hpp"
#include <filesystem>
#include <stb/stb_image.h>
#include <vector>

class Texture
{
  public:
    Texture(unsigned int width, unsigned int height) : m_logger("Texture") {}
    Texture(const std::filesystem::path &path) : m_logger("Texture")
    {
        const std::string pathStr = path.string();

        int width, height;
        stbi_uc *data =
            stbi_load(pathStr.c_str(), &width, &height, NULL, STBI_rgb_alpha);

        if (!data)
        {
            m_logger.log(Logger::Severity::Error, "Texture()",
                         "Failed to load: " + pathStr);
            return;
        }

        m_size.x = static_cast<unsigned int>(width);
        m_size.y = static_cast<unsigned int>(height);

        m_pixels.resize(width * height);

        for (int i = 0; i < width * height; ++i)
        {
            int dataIndex = i * 4;

            Color color;
            color.r = data[dataIndex];
            color.g = data[dataIndex + 1];
            color.b = data[dataIndex + 2];
            m_pixels[i] = color;
        }

        stbi_image_free(data);

        m_logger.log(Logger::Severity::Info, "Texture()",
                     "Successfully loaded: " + pathStr);
    }

    Vec2<unsigned int> getSize() const { return m_size; }

    Color getPixel(unsigned int x, unsigned int y) const
    {
        if (x >= m_size.x || y >= m_size.y)
        {
            return Color();
        }

        return m_pixels[Utils::Index::index_2dto1d(x, y, m_size.x)];
    }

    const std::vector<Color> &getPixels() const { return m_pixels; }

  private:
    Vec2<unsigned int> m_size;
    std::vector<Color> m_pixels;

    Logger m_logger;
};
