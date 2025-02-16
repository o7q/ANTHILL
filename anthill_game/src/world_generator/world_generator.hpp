#pragma once

#include "wg_settings.hpp"
#include "../world/world.hpp"

#include "generators/test/test.hpp"

namespace WorldGenerator
{
    World *generate(SDL_Renderer *renderer, Settings settings);
}