#include "entities/wuskkogel/wuskkogel.hpp"
#include "math/perlin.hpp"
#include "world/particle_handler/particle.hpp"
#include "world_generator/generate_result.hpp"
#include <cstdint>
#include <memory>

GenerateResult generate_desert_layer1(Vec2i pos, uint32_t seed, const Assets &assets)
{
    GenerateResult result;

    float p0 = Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, seed);
    float p1 = Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 9, seed);

    Particle::MatterType matterType   = Particle::MatterType::Solid;
    Particle::PhysicsType physicsType = Particle::PhysicsType::Sand;
    Color color(255, 159, 0);
    if (p1 > 0.4f)
    {
        color = Color(255, 179, 54);
    }
    if (p1 > 0.5f)
    {
        color       = Color(255, 197, 102);
        physicsType = Particle::PhysicsType::None;
    }
    if (p1 > 0.59f)
    {
        color = Color(255, 219, 161);
    }

    if (p0 > 0.60f && p0 < 0.75f)
    {
        matterType = Particle::MatterType::Gas;
        color      = Color();
    }

    if (p0 >= 0.67f && p0 < 0.68f && Math::Random::unseededRandomInt(0, 15000) == 0)
    {
        auto wuskkogel = std::make_unique<Wuskkogel>(assets);
        wuskkogel->getBody().setPosition(pos);
        result.spawnEntity = std::move(wuskkogel);
    }

    result.particle.setColor(color);
    result.particle.setMatterType(matterType);
    result.particle.setPhysicsType(physicsType);

    return result;
}

GenerateResult generate_desert_layer2(Vec2i pos, uint32_t seed, const Assets &assets)
{
    GenerateResult result;

    float p0 = Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, seed);

    Particle::MatterType matterType = Particle::MatterType::Solid;
    Color color(255, 159, 0);
    if (p0 > 0.4f)
    {
        color = Color(255, 179, 54);
    }
    if (p0 > 0.5f)
    {
        color = Color(255, 197, 102);
    }
    if (p0 > 0.60f && p0 < 0.75f)
    {
        matterType = Particle::MatterType::Gas;
        color      = Color();
    }
    if (p0 > 0.1f && p0 < 0.3f)
    {
        matterType = Particle::MatterType::Gas;
        color      = Color();
    }

    if (p0 > 0.65f && p0 < 0.70f && Math::Random::unseededRandomInt(0, 15000) == 0)
    {
        auto wuskkogel = std::make_unique<Wuskkogel>(assets);
        wuskkogel->getBody().setPosition(pos);
        result.spawnEntity = std::move(wuskkogel);
    }

    result.particle.setColor(color);
    result.particle.setMatterType(matterType);

    return result;
}
