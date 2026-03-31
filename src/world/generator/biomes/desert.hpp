#pragma once

#include "math/perlin.hpp"
#include "math/random.hpp"
#include "world/particle/particle.hpp"
#include <cstdint>

inline Particle generate_desert(Vec2i pos, uint64_t seed)
{
    if (pos.y < 0)
    {
        return Particle();
    }
    float v = Math::Perlin::sampleEx(pos.toFloat(), {300, 200}, 5, seed);

    Particle p;

    if (v >= 0.3f)
    {
        Color c(47, 7, 0);

        p.setPhysicsType(Particle::PhysicsType::None);
        p.setMatterType(Particle::MatterType::Solid);
        p.setRestitution(0.3f);

        if (v <= 0.98f)
        {
            c = Color(49, 13, 0);
        }
        if (v <= 0.95f)
        {
            c = Color(61, 26, 0);
        }
        if (v <= 0.8f)
        {
            c = Color(87, 55, 1);
        }
        if (v <= 0.69f)
        {
            c = Color(106, 71, 20);
        }
        if (v <= 0.6f)
        {
            c = Color(155, 113, 49);
        }
        if (v <= 0.55f)
        {
            c = Color(168, 122, 63);
        }
        if (v <= 0.5f)
        {
            c = Color(189, 143, 85);
        }
        if (v <= 0.49f)
        {
            c = Color(214, 173, 120);
        }
        if (v <= 0.41f)
        {
            c = Color(227, 191, 145);
        }
        if (v <= 0.31f)
        {
            c = Color(212, 186, 161);
        }

        float noise = Math::Random::weakRandInt(94, 100) / 100.0f;

        c.r *= noise;
        c.g *= noise;
        c.b *= noise;

        p.setColor(c);
    }

    return p;
}
