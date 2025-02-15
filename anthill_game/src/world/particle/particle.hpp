#pragma once

#include "../../engine/math/color.hpp"
#include "../../engine/math/vector.hpp"
#include "../../engine/math/random.hpp"

struct Particle
{
    enum class Preset
    {
        Air,
        Stone,
        Sand,
        Water,
        Blood,
        Steam
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
        None,
        Sand,
        Water,
        Smoke,
        Goop
    };

    enum class PCollisionType
    {
        None,
        Solid,
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

    bool isAir()
    {
        return p_state == PState::Gas && p_mode == PMode::None;
    }

    PState p_state = PState::Gas;
    PMode p_mode = PMode::None;
    PCollisionType p_collision_type = PCollisionType::None;
    bool solid_enable_collision = true;

    float f_value1 = 0.0f;
    float f_value2 = 0.0f;
    float f_value3 = 0.0f;

    Color color = Color(0, 0, 0, 0);
    Color mix_color = Color(0, 0, 0, 0);

    PMode hybrid;
};