#pragma once

#include "../wg_settings.hpp"
#include "../../world/world.hpp"
#include "../../engine/math/random.hpp"

namespace WorldGenerator
{
    class Generator
    {
    public:
        Generator(Settings settings);
        World *world();

    protected:
        int i_rand(int min, int max);
        float f_rand(float min, float max);

    protected:
        World *m_world = nullptr;
        Settings m_settings;

    private:
        std::mt19937 m_gen;
    };
}