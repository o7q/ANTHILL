#pragma once

#include "../wg_settings.hpp"
#include "../../world/world.hpp"
#include "../../engine/math/random.hpp"

#include "../../engine/math/noise/perlin.hpp"

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

        struct PerlinSampler
        {
            PerlinSampler(PerlinNoise &noise) : m_noise(noise) {}

            float sample(int x, int y);

            void setXScale(float scale_x);
            void setYScale(float scale_y);
            void setIterations(int iterations);

        private:
            float m_scale_x = 1.0f;
            float m_scale_y = 1.0f;
            int m_iterations = 1;

        private:
            PerlinNoise &m_noise;
        };

    protected:
        World *m_world = nullptr;
        Settings m_settings;

    private:
        std::mt19937 m_gen;
    };
}