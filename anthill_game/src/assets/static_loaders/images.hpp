#pragma once

#include <SDL3_image/SDL_image.h>

#include "../../engine/assets/image.hpp"

struct Images
{
    Images()
    {
        crosshair_1x.create("assets/images/crosshair/crosshair_1x.png");
        crosshair_2x.create("assets/images/crosshair/crosshair_2x.png");
    }

    Image crosshair_1x;
    Image crosshair_2x;
};