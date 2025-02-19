#pragma once

#include <algorithm>

#include "../generator.hpp"

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