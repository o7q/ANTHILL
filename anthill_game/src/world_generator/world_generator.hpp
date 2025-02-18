#pragma once

#include <atomic>

#include "wg_settings.hpp"
#include "../world/world.hpp"

#include "generators/test/test.hpp"
#include "generators/jungle/jungle.hpp"

namespace WorldGenerator
{
    class ThreadSafeGenerator
    {
    public:
        ThreadSafeGenerator(Settings settings);

        void generate();
        bool finished();

        World *getWorld();

    private:
        Settings m_settings;

        World *m_world = nullptr;
        std::atomic<bool> m_finished = false;
    };
}