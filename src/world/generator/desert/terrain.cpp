#include "math/perlin.hpp"
#include "math/random.hpp"
#include "world/particle_world/particle.hpp"
#include <cstdint>

Particle generate_desert_terrain0(Vec2i pos, uint32_t seed)
{
    float v = Math::Perlin::sampleEx(pos.toFloat(), {300, 200}, 4, seed);

    Particle p;

    if (v >= 0.3f)
    {
        Color c(106, 71, 20);

        p.setMatterType(Particle::MatterType::Solid);
        p.setRestitution(0.3f);
        if (v <= 0.7f)
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

        float noise = Math::Random::weakRandInt(94, 100) / 100.0f;

        c.r *= noise;
        c.g *= noise;
        c.b *= noise;

        p.setColor(c);
    }

    return p;
}

Particle generate_desert_terrain1(Vec2i pos, uint32_t seed)
{
    float v = Math::Perlin::sampleEx(pos.toFloat(), {300, 200}, 4, seed);

    Particle p;

    if (v >= 0.3f)
    {
        Color c(106, 71, 20);

        p.setMatterType(Particle::MatterType::Solid);
        p.setRestitution(0.3f);
        if (v <= 0.7f)
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

        float noise = Math::Random::weakRandInt(94, 100) / 100.0f;

        c.r *= noise;
        c.g *= noise;
        c.b *= noise;

        c.r *= 0.9f;
        c.g *= 0.85f;
        c.b *= 0.8f;

        p.setColor(c);
    }

    return p;
}
