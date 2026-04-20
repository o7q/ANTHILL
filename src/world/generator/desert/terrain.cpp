#include "math/numbers.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/voronoi.hpp"
#include "world/particle_world/particle.hpp"
#include <cstdint>

Particle generate_desert_layer1(Vec2i pos, uint32_t seed)
{
    Particle p;

    float p0 =
        Math::Perlin::sampleEx(pos.toFloat() / 2000.0f, {1.0f, 1.0f}, 7, seed) -
        0.5f;
    int modifier = static_cast<int>(p0 * 13000.0f);
    if (Math::Numbers::between(std::abs(pos.x + modifier) % 3000, 0, 800))
    {
        // air
    }
    else
    {
        Color c(163, 131, 90);

        float p1 = p0 + 0.5f;
        if (p1 <= 0.95f)
        {
            c = Color(176, 142, 99);
        }
        if (p1 <= 0.9f)
        {
            c = Color(191, 153, 105);
        }
        if (p1 <= 0.7f)
        {
            c = Color(199, 160, 111);
        }
        if (p1 <= 0.68f)
        {
            c = Color(207, 167, 116);
        }
        if (p1 <= 0.6f)
        {
            c = Color(212, 172, 121);
        }
        if (p1 <= 0.5f)
        {
            c = Color(222, 181, 129);
        }
        if (p1 <= 0.4f)
        {
            c = Color(230, 188, 135);
        }

        float perlin =
            Math::Perlin::sampleEx(pos.toFloat() / 900.0f, {1, 1}, 6, seed) -
            0.5f;

        Math::Voronoi::Sample voronoi = Math::Voronoi::sampleEx(
            pos.toFloat() + perlin * 500, {100, 100}, seed);
        uint32_t hash = Math::Random::hashFromPosition(voronoi.cell, seed);

        if (hash % 3 == 0)
        {
            c = Color(227, 178, 116);
        }

        float noise = Math::Random::weakRandInt(94, 100) / 100.0f;

        c.r *= noise;
        c.g *= noise;
        c.b *= noise;

        p.setColor(c);
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::Sand);
    }

    return p;
}

Particle generate_desert_layer2(Vec2i pos, uint32_t seed)
{
    Particle p;

    float p0 =
        Math::Perlin::sampleEx(pos.toFloat() / 2000.0f, {1.9f, 1.0f}, 7, seed) -
        0.5f;
    int modifier = static_cast<int>(p0 * 13000.0f);
    if (Math::Numbers::between(std::abs(pos.x + modifier) % 3000, 0, 800))
    {
        // air
    }
    else
    {
        Color c(106, 71, 20);

        float p1 = p0 + 0.5f;
        if (p1 <= 0.9f)
        {
            c = Color(155, 113, 49);
        }
        if (p1 <= 0.7f)
        {
            c = Color(168, 122, 63);
        }
        if (p1 <= 0.68f)
        {
            c = Color(189, 143, 85);
        }
        if (p1 <= 0.6f)
        {
            c = Color(214, 173, 120);
        }
        if (p1 <= 0.5f)
        {
            c = Color(227, 191, 145);
        }
        if (p1 <= 0.4f)
        {
            c = Color(230, 188, 135);
        }

        float noise = Math::Random::weakRandInt(94, 100) / 100.0f;

        c.r *= noise;
        c.g *= noise;
        c.b *= noise;

        p.setColor(c);
        p.setMatterType(Particle::MatterType::Solid);
        p.setPhysicsType(Particle::PhysicsType::Sand);
    }

    return p;
}
