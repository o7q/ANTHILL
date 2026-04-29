#include "world_generator.hpp"
#include "math/random.hpp"

WorldGenerator::WorldGenerator(World &world, const Assets &assets) : r_world(world), r_assets(assets)
{
    m_seed = Math::Random::unseededRandomInt(0, 10000000);
}

void WorldGenerator::generate(Vec2i origin, Vec2i radius) { place_terrain(origin, radius); }
