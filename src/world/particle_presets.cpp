#include "particle.hpp"

Particle::Particle(Preset particlePreset)
{
    switch (particlePreset)
    {
    case Preset::Sand:
    {
        p_state = PState::Solid;
        p_mode = PMode::Sand;

        float random_dark = Random::genFloat(0.8, 1.0f);
        color = Color(255 * random_dark,
                      227 * random_dark,
                      150 * random_dark,
                      255);
    }
    break;
    case Preset::Water:
    {
        p_state = PState::Liquid;
        p_mode = PMode::Water;

        color = Color(31, 169, 255, 200);
        liquid_absorption_color = Color(51, 51, 51, 255);
    }
    break;
    case Preset::Blood:
    {
        p_state = PState::Liquid;
        p_mode = PMode::Water;

        color = Color(252, 8, 8, 250);
        liquid_absorption_color = Color(166, 0, 0, 255);
    }
    break;
    }
}