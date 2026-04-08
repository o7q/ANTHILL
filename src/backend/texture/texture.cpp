#include "texture.hpp"

#include "backend/logger/logger.hpp"
#include "math/index.hpp"

Texture::Texture() { initNull(); }
Texture::Texture(Vec2u size)
{
    m_size = size;

    m_pixels.resize(size.x * size.y);

    Logger::info("Texture::Texture()",
                 "Successfully created a blank texture of size: " +
                     std::to_string(size.x) + "x" + std::to_string(size.y));
}
Texture::Texture(const std::filesystem::path &path)
{
    const std::string pathString = path.string();

    int width, height;
    stbi_uc *data =
        stbi_load(pathString.c_str(), &width, &height, NULL, STBI_rgb_alpha);

    if (!data)
    {
        Logger::error("Texture::Texture()", "Failed to load: " + pathString);

        initNull();
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
        color.a = data[dataIndex + 3];
        m_pixels[i] = color;
    }

    stbi_image_free(data);

    Logger::info("Texture::Texture()", "Successfully loaded: " + pathString);
}

void Texture::setPixel(Vec2u pos, Color color)
{
    if (pos.x >= m_size.x || pos.y >= m_size.y)
    {
        return;
    }

    m_pixels[Math::Index::index_2dto1d(pos, m_size.x)] = color;
}

Color Texture::getPixel(Vec2u pos) const
{
    if (pos.x >= m_size.x || pos.y >= m_size.y)
    {
        return Color();
    }

    return m_pixels[Math::Index::index_2dto1d(pos, m_size.x)];
}

void Texture::initNull()
{
    unsigned int size = 31;

    m_size.x = static_cast<unsigned int>(size);
    m_size.y = static_cast<unsigned int>(size);

    m_pixels.resize(size * size);

    for (unsigned int i = 0; i < size * size; ++i)
    {
        m_pixels[i] = i % 2 == 0 ? Color(255, 0, 255) : Color(0, 0, 0);
    }
}
