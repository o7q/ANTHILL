#pragma once

#include <limits>

#include "../engine/math/random.hpp"

namespace WorldGenerator
{
    struct Settings
    {
        enum class Preset
        {
            Test
        };

        Settings() = default;
        Settings(int width, int height, int seed, Preset preset)
        {
            this->width = width;
            this->height = height;

            if (seed < 0)
            {
                this->seed = Random::genInt(0, std::numeric_limits<int>::max());
            }

            this->preset = preset;
        }

        int width = 0;
        int height = 0;

        int seed = -1;

        Preset preset;
    };
}