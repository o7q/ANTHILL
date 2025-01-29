#pragma once

#include "../types.hpp"

struct Particle
{
    enum class PState
    {
        Solid,
        Liquid,
        Gas
    };

    enum class PMode
    {
        NoGravity,
        Sand,
        Water
    };

    PState p_state = PState::Gas;
    PMode p_mode = PMode::NoGravity;

    Uint32 color = 0x00000000;
};