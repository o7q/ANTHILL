#include "world_generator.hpp"

#include "core/math/random.hpp"

WorldGenerator::WorldGenerator(World &world, const Assets &assets)
    : r_world(world), r_assets(assets), m_structureLayer({32, 32})
{
    m_seed = Math::Random::unseededRandomInt(0, 10000000);
}

void WorldGenerator::generate(Vec2i origin, Vec2i radius)
{
    generate_place(origin, radius);
}
