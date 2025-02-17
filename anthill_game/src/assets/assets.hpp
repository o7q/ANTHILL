#pragma once

#include "static_loaders/surfaces.hpp"
#include "static_loaders/fonts.hpp"

struct Assets
{
    void load()
    {
        surfaces.load();
        fonts.load();
    }

    void destroy()
    {
        surfaces.destroy();
        fonts.destroy();
    }

    Surfaces surfaces;
    Fonts fonts;
};