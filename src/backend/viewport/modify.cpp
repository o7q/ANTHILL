#include "math/interpolation.hpp"
#include "viewport.hpp"

void Viewport::setPixel(unsigned int x, unsigned int y, Color color)
{
    if (x >= m_size.x || y >= m_size.y)
    {
        return;
    }

    const unsigned int index = get_pixel_index(x, y);

    if (color.a != 255)
    {
        float a = color.a / 255.0f;
        float inv_a = 1.0f - a;

        Color current = getPixel(x, y);
        color.r = a * color.r + inv_a * current.r;
        color.g = a * color.g + inv_a * current.g;
        color.b = a * color.b + inv_a * current.b;
    }

    m_pixels[index] = color.r;
    m_pixels[index + 1] = color.g;
    m_pixels[index + 2] = color.b;

    if (x < m_update_pos1.x)
    {
        m_update_pos1.x = x;
    }
    if (y < m_update_pos1.y)
    {
        m_update_pos1.y = y;
    }
    if (x > m_update_pos2.x)
    {
        m_update_pos2.x = x;
    }
    if (y > m_update_pos2.y)
    {
        m_update_pos2.y = y;
    }

    m_update_rect.x = m_update_pos1.x;
    m_update_rect.y = m_update_pos1.y;
    m_update_rect.w = m_update_pos2.x - m_update_pos1.x + 1;
    m_update_rect.h = m_update_pos2.y - m_update_pos1.y + 1;

    m_pixelChanged = true;
}

Color Viewport::getPixel(unsigned int x, unsigned int y)
{
    if (x >= m_size.x || y >= m_size.y)
    {
        return Color();
    }

    const unsigned int index = get_pixel_index(x, y);
    return Color(m_pixels[index], m_pixels[index + 1], m_pixels[index + 2]);
}
