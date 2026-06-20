#include "world_generator/world_generator.hpp"

#include "entities/wuskkogel/wuskkogel.hpp"
#include "px/utils/perlin.hpp"
#include "world/particle_handler/particle.hpp"
#include "world_generator/spawn_data.hpp"
#include <functional>
#include <memory>
#include <vector>

PositionalSpawnData WorldGenerator::generate_desert_layer1(px::Vec2i pos)
{
    PositionalSpawnData data;

    float p0 = px::Utils::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, m_seed);
    float p1 = px::Utils::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 9, m_seed);

    Particle::MatterType matterType   = Particle::MatterType::Solid;
    Particle::PhysicsType physicsType = Particle::PhysicsType::Sandstone;
    px::Color color(255, 159, 0);
    if (p1 > 0.4f)
    {
        color = px::Color(255, 179, 54);
    }
    if (p1 > 0.5f)
    {
        color       = px::Color(255, 197, 102);
        physicsType = Particle::PhysicsType::None;
    }
    if (p1 > 0.59f)
    {
        color = px::Color(255, 219, 161);
    }
    if (p0 > 0.60f && p0 < 0.75f)
    {
        color      = px::Color();
        matterType = Particle::MatterType::Gas;
    }

    if (p0 >= 0.67f && p0 < 0.68f && px::Utils::Random::unseededRandomInt(0, 10000) == 0)
    {
        data.entities = [](px::Vec2i position, const Assets &assets)
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

PositionalSpawnData WorldGenerator::generate_desert_layer2(px::Vec2i pos)
{
    PositionalSpawnData data;

    float p0 = px::Utils::Perlin::sampleEx(pos.toFloat(), {1000.0f, 1000.0f}, 6, m_seed);

    Particle::MatterType matterType = Particle::MatterType::Solid;
    px::Color color(255, 159, 0);
    if (p0 > 0.4f)
    {
        color = px::Color(255, 179, 54);
    }
    if (p0 > 0.5f)
    {
        color = px::Color(255, 197, 102);
    }
    if (p0 >= 0.65f && p0 <= 0.75f)
    {
        matterType = Particle::MatterType::Gas;
        color      = {};
    }

    if (p0 > 0.65f && p0 < 0.70f && px::Utils::Random::unseededRandomInt(0, 10000) == 0)
    {
        data.entities = [](px::Vec2i position, const Assets &assets)
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
