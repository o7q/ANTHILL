#pragma once

#include <algorithm>

#include "../generator.hpp"

#include "../../../engine/math/noise/perlin.hpp"

namespace WorldGenerator
{
    class JungleGenerator : public Generator
    {
    public:
        JungleGenerator(Settings settings) : Generator(settings)
        {
            generate_terrain();
        }

    private:
        void generate_terrain();
    };
}