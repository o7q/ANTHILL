#include "texture.hpp"

void Texture::update_sdl_transforms()
{
    src_rect.x = 0;
    src_rect.y = 0;
    src_rect.w = size.x;
    src_rect.h = size.y;

    dst_rect.x = position.x - size.x / 2;
    dst_rect.y = position.y - size.y / 2;
    dst_rect.w = size.x;
    dst_rect.h = size.y;

    center_point.x = size.x / 2;
    center_point.y = size.y / 2;
}

void Texture::reset_update_rect()
{
    update_rect.x = 0;
    update_rect.y = 0;
    update_rect.w = size.x;
    update_rect.h = size.y;
}