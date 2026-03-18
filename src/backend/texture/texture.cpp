#include "texture.hpp"

#include "math/index.hpp"

Texture::Texture() : m_logger("Texture") { initNull(); }
Texture::Texture(unsigned int width, unsigned int height) : m_logger("Texture")
{
    m_size.x = static_cast<unsigned int>(width);
    m_size.y = static_cast<unsigned int>(height);

    m_pixels.resize(width * height);

    m_logger.log(Logger::Severity::Info, "Texture()",
                 "Successfully created a blank texture of size: " +
                     std::to_string(width) + "x" + std::to_string(height));
}
Texture::Texture(const std::filesystem::path &path) : m_logger("Texture")
{
    const std::string pathStr = path.string();

    int width, height;
    stbi_uc *data =
        stbi_load(pathStr.c_str(), &width, &height, NULL, STBI_rgb_alpha);

    if (!data)
    {
        m_logger.log(Logger::Severity::Error, "Texture()",
                     "Failed to load: " + pathStr);

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

    m_logger.log(Logger::Severity::Info, "Texture()",
                 "Successfully loaded: " + pathStr);
}

Color Texture::getPixel(unsigned int x, unsigned int y) const
{
    if (x >= m_size.x || y >= m_size.y)
    {
        return Color();
    }

    return m_pixels[Utils::Index::index_2dto1d(x, y, m_size.x)];
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
