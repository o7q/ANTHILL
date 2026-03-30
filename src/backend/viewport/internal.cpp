#include "viewport.hpp"

#include "math/index.hpp"
#include <limits>

void Viewport::update_pixel_changes()
{
    if (!m_pixelChanged)
    {
        return;
    }

    const unsigned int index =
        get_pixel_index(Vec2u(m_update_rect.x, m_update_rect.y));

    SDL_UpdateTexture(m_texture, &m_update_rect, &m_pixels[index],
                      m_size.x * 3);
    reset_update_points();

    m_pixelChanged = false;
}

void Viewport::reset_update_points()
{
    m_update_pos1.x = std::numeric_limits<unsigned int>::max();
    m_update_pos1.y = std::numeric_limits<unsigned int>::max();
    m_update_pos2.x = 0u;
    m_update_pos2.y = 0u;
}

unsigned int Viewport::get_pixel_index(Vec2u pos)
{
    return Math::Index::index_2dto1d(pos, m_size.x) * 3u;
}
