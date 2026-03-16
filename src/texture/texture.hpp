#pragma once

#include "backend/utils/color.hpp"
#include "backend/utils/index.hpp"
#include "backend/utils/vec.hpp"
#include <filesystem>
#include <iostream>
#include <stb/stb_image.h>
#include <vector>

class Texture
{
  public:
    Texture(const std::filesystem::path &path)
    {
        const std::string pathStr = path.string();
        const char *pathStr2 = path.c_str();

        int width, height;
        stbi_uc *data =
            stbi_load(pathStr2, &width, &height, NULL, STBI_rgb_alpha);

        if (!data)
        {
            std::cout << "ERR" << std::endl;
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
    }

    Vec2<unsigned int> getSize() const { return m_size; }

    Color getPixel(unsigned int x, unsigned int y) const
    {
        if (x >= m_size.x || y >= m_size.y)
        {
            return Color();
        }

        return m_pixels[Backend::Utils::Index::index_2dto1d(x, y, m_size.x)];
    }

    const std::vector<Color> &getPixels() const { return m_pixels; }

  private:
    Vec2<unsigned int> m_size;
    std::vector<Color> m_pixels;
};
