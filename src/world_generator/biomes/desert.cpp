#include "entities/wuskkogel/wuskkogel.hpp"
#include "math/perlin.hpp"
#include "math/random.hpp"
#include "world/particle_handler/particle.hpp"
#include "world_generator/generate_result.hpp"
#include <cstdint>
#include <memory>

GenerateResult generate_desert_layer1(Vec2i pos, uint32_t seed,
                                      const Assets &assets)
{
    GenerateResult result;

    float p0 =
        Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, seed);
    float p1 =
        Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 8, seed);

    Particle::MatterType matterType = Particle::MatterType::Solid;
    Color color(186, 144, 89);
    if (p1 > 0.1f)
    {
        color = Color(196, 153, 98);
    }
    if (p1 > 0.2f)
    {
        color = Color(204, 162, 108);
    }
    if (p1 > 0.3f)
    {
        color = Color(209, 167, 113);
    }
    if (p1 > 0.4f)
    {
        color = Color(219, 177, 123);
    }
    if (p1 > 0.45f)
    {
        color = Color(230, 188, 135);
    }
    if (p1 > 0.5f)
    {
        color = Color(232, 191, 139);
    }
    if (p1 > 0.52f)
    {
        color = Color(235, 193, 141);
    }
    if (p1 > 0.55f)
    {
        color = Color(237, 197, 147);
    }
    if (p0 > 0.60f && p0 < 0.75f)
    {
        matterType = Particle::MatterType::Gas;
        color = Color();
    }

    if (p0 >= 0.67f && p0 < 0.68f &&
        Math::Random::unseededRandomInt(0, 15000) == 0)
    {
        auto wuskkogel = std::make_unique<Wuskkogel>(assets);
        wuskkogel->getBody().setPosition(pos);
        result.spawnEntity = std::move(wuskkogel);
    }

    float brightness = Math::Random::unseededRandomInt(97, 100) / 100.0f;

    color.r *= brightness;
    color.g *= brightness;
    color.b *= brightness;

    result.particle.setColor(color);
    result.particle.setMatterType(matterType);

    return result;
}

GenerateResult generate_desert_layer2(Vec2i pos, uint32_t seed,
                                      const Assets &assets)
{
    GenerateResult result;

    float p0 =
        Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, seed);
    float p1 =
        Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 8, seed);

    Particle::MatterType matterType = Particle::MatterType::Solid;
    Color color(186, 144, 89);
    if (p1 > 0.1f)
    {
        color = Color(168, 147, 119);
    }
    if (p1 > 0.2f)
    {
        color = Color(204, 162, 108);
    }
    if (p1 > 0.3f)
    {
        color = Color(209, 167, 113);
    }
    if (p1 > 0.4f)
    {
        color = Color(219, 177, 123);
    }
    if (p1 > 0.45f)
    {
        color = Color(181, 150, 109);
    }
    if (p1 > 0.5f)
    {
        color = Color(201, 165, 117);
    }
    if (p1 > 0.52f)
    {
        color = Color(219, 183, 134);
    }
    if (p1 > 0.55f)
    {
        color = Color(237, 197, 147);
    }

    if (p0 > 0.60f && p0 < 0.75f)
    {
        matterType = Particle::MatterType::Gas;
        color = Color();
    }
    if (p0 > 0.1f && p0 < 0.3f)
    {
        matterType = Particle::MatterType::Gas;
        color = Color();
    }

    if (p0 > 0.65f && p0 < 0.70f &&
        Math::Random::unseededRandomInt(0, 15000) == 0)
    {
        auto wuskkogel = std::make_unique<Wuskkogel>(assets);
        wuskkogel->getBody().setPosition(pos);
        result.spawnEntity = std::move(wuskkogel);
    }

    float brightness = Math::Random::unseededRandomInt(97, 100) / 100.0f;

    color.r *= brightness;
    color.g *= brightness;
    color.b *= brightness;

    result.particle.setColor(color);
    result.particle.setMatterType(matterType);

    return result;
}
