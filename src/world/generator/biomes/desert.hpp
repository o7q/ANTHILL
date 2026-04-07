#pragma once

#include "math/perlin.hpp"
#include "math/random.hpp"
#include "world/particle_world/particle.hpp"
#include <cstdint>

inline Particle generate_desert(Vec2i pos, uint32_t seed)
{
    if (pos.y < 0)
    {
        return Particle();
    }
    float v = Math::Perlin::sampleEx(pos.toFloat(), {300, 200}, 4, seed);

    Particle p;

    if (v >= 0.3f)
    {
        Color c(47, 7, 0);

        p.setMatterType(Particle::MatterType::Solid);
        p.setRestitution(0.3f);

        if (v <= 0.98f)
        {
            c = Color(49, 13, 0);
            p.setPhysicsType(Particle::PhysicsType::None);
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
            p.setPhysicsType(Particle::PhysicsType::Sand);
        }
        if (v <= 0.49f)
        {
            c = Color(214, 173, 120);
            p.setPhysicsType(Particle::PhysicsType::Sand);
        }
        if (v <= 0.41f)
        {
            c = Color(227, 191, 145);
            p.setPhysicsType(Particle::PhysicsType::None);
        }
        if (v <= 0.31f)
        {
            c = Color(230, 188, 135);
        }

        float v2 = Math::Perlin::sampleEx(pos.toFloat(), {200, 200}, 10, seed);
        float v3 = Math::Perlin::sampleEx(pos.toFloat(), {150, 20}, 10, seed);

        if (v2 >= 0.99f)
        {
            c.r *= 0.9f;
            c.g *= 0.9f;
            c.b *= 0.5f;
        }

        if (v3 > 0.94f)
        {
            c.r *= 0.95f;
            c.g *= 0.93f;
            c.b *= 0.9f;
        }

        float noise = Math::Random::weakRandInt(94, 100) / 100.0f;

        c.r *= noise;
        c.g *= noise;
        c.b *= noise;

        p.setColor(c);
    }

    return p;
}
