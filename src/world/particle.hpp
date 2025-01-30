#pragma once

#include "../math/color.hpp"
// #include "../math/vector.hpp"
#include "../math/random.hpp"

struct Particle
{
    enum class Preset
    {
        Sand,
        Water,
        Blood
    };

    Particle() = default;
    Particle(Preset particlePreset);

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

    float liquid_saturation = 0.0f;

    Color color = Color(0, 0, 0, 0);
    Color liquid_absorption_color = Color(0, 0, 0, 0);
};