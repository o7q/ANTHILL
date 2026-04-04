#include "viewport.hpp"

void Viewport::set_pixel(Vec2u pos, Color color)
{
    if (pos.x >= m_size.x || pos.y >= m_size.y)
    {
        return;
    }

    const unsigned int index = get_pixel_index(pos);

    if (color.a != 255)
    {
        float a = color.a / 255.0f;
        float inv_a = 1.0f - a;

        Color current = get_pixel(pos);
        color.r = a * color.r + inv_a * current.r;
        color.g = a * color.g + inv_a * current.g;
        color.b = a * color.b + inv_a * current.b;
    }

    m_pixels[index] = color.r;
    m_pixels[index + 1] = color.g;
    m_pixels[index + 2] = color.b;

    if (pos.x < m_update_pos1.x)
    {
        m_update_pos1.x = pos.x;
    }
    if (pos.y < m_update_pos1.y)
    {
        m_update_pos1.y = pos.y;
    }
    if (pos.x > m_update_pos2.x)
    {
        m_update_pos2.x = pos.x;
    }
    if (pos.y > m_update_pos2.y)
    {
        m_update_pos2.y = pos.y;
    }

    m_update_rect.x = m_update_pos1.x;
    m_update_rect.y = m_update_pos1.y;
    m_update_rect.w = m_update_pos2.x - m_update_pos1.x + 1;
    m_update_rect.h = m_update_pos2.y - m_update_pos1.y + 1;

    m_pixelChanged = true;
}

Color Viewport::get_pixel(Vec2u pos)
{
    const unsigned int index = get_pixel_index(pos);
    return Color(m_pixels[index], m_pixels[index + 1], m_pixels[index + 2]);
}
