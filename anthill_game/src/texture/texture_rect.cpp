#include "texture.hpp"

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

void Texture::reset_update_rect()
{
    m_update_rect.x = 0;
    m_update_rect.y = 0;
    m_update_rect.w = m_size.x;
    m_update_rect.h = m_size.y;
}