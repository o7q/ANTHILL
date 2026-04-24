#include "math/numbers.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "math/voronoi.hpp"
#include "world/particle_handler/particle.hpp"
#include <cstdint>

Particle generate_desert_layer1(Vec2i pos, uint32_t seed)
{
    Particle p;

    float p0 =
        Math::Perlin::sampleEx(pos.toFloat(), {100.0f, 100.0f}, 4, seed);

    if (p0 < 0.7f)
    {
        p.setColor(Color(255, 0, 0));
        p.setMatterType(Particle::MatterType::Solid);
    }

    return p;
}

Particle generate_desert_layer2(Vec2i pos, uint32_t seed)
{
    Particle p;

    float p0 =
        Math::Perlin::sampleEx(pos.toFloat(), {10.0f, 10.0f}, 1, seed);

    if (p0 > 0.5f)
    {
    }
    p.setColor(Color(255, 255, 0));
    p.setMatterType(Particle::MatterType::Solid);

    return p;
}
