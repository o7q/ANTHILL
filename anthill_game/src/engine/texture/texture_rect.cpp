#include "texture.hpp"

#include <limits>

void Texture::update_sdl_transforms()
{
    m_src_rect.x = 0;
    m_src_rect.y = 0;
    m_src_rect.w = m_size.x;
    m_src_rect.h = m_size.y;

    m_dst_rect.x = m_position.x - m_origin.x;
    m_dst_rect.y = m_position.y - m_origin.y;
    m_dst_rect.w = m_size.x;
    m_dst_rect.h = m_size.y;
}

void Texture::reset_update_points()
{
    m_update_pos1.x = std::numeric_limits<int>::max();
    m_update_pos1.y = std::numeric_limits<int>::max();
    m_update_pos2.x = std::numeric_limits<int>::min();
    m_update_pos2.y = std::numeric_limits<int>::min();
}