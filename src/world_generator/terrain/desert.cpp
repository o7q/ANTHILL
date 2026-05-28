#include "world_generator/world_generator.hpp"

#include "core/math/perlin.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"
#include "world/particle_handler/particle.hpp"
#include "world_generator/spawn_data.hpp"
#include <functional>
#include <memory>
#include <vector>

PositionalSpawnData WorldGenerator::generate_desert_layer1(Vec2i pos)
{
    PositionalSpawnData data;

    float p0 = Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, m_seed);
    float p1 = Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 9, m_seed);

    Particle::MatterType matterType   = Particle::MatterType::Solid;
    Particle::PhysicsType physicsType = Particle::PhysicsType::Sandstone;
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

    if (p0 >= 0.67f && p0 < 0.68f && Math::Random::unseededRandomInt(0, 10000) == 0)
    {
        data.entities = [](Vec2i position, const Assets &assets)
        {
            std::vector<std::unique_ptr<Entity>> entities;
            auto wuskkogel = std::make_unique<Wuskkogel>(assets);
            wuskkogel->getBody().setPosition(position);
            entities.push_back(std::move(wuskkogel));
            return entities;
        };
    }

    data.particle.setColor(color);
    data.particle.setMatterType(matterType);
    data.particle.setPhysicsType(physicsType);

    return data;
}

PositionalSpawnData WorldGenerator::generate_desert_layer2(Vec2i pos)
{
    PositionalSpawnData data;

    float p0 = Math::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, m_seed);

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
    if (p0 >= 0.65f && p0 <= 0.75f)
    {
        matterType = Particle::MatterType::Gas;
        color      = Color{};
    }

    if (p0 > 0.65f && p0 < 0.70f && Math::Random::unseededRandomInt(0, 10000) == 0)
    {
        data.entities = [](Vec2i position, const Assets &assets)
        {
            std::vector<std::unique_ptr<Entity>> entities;
            auto wuskkogel = std::make_unique<Wuskkogel>(assets);
            wuskkogel->getBody().setPosition(position);
            entities.push_back(std::move(wuskkogel));
            return entities;
        };
    }

    data.particle.setColor(color);
    data.particle.setMatterType(matterType);

    return data;
}
