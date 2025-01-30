#pragma once

#include "../math/color.hpp"
#include "../math/vector.hpp"

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

    bool isSolidPassable()
    {
        return p_state == PState::Gas || p_state == PState::Liquid;
    }

    bool isLiquidPassable()
    {
        return p_state == PState::Gas;
    }

    PState p_state = PState::Gas;
    PMode p_mode = PMode::NoGravity;

    Color color;

    Vec2<float> velocity = Vec2<float>(0.0f, 1.0f);
};