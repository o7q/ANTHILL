#include "world_generator.hpp"
#include "math/random.hpp"

WorldGenerator::WorldGenerator(World &world)
    : r_world(world), m_structureLayer({32, 32})
{
    m_seed = Math::Random::weakRandInt(0, 10000000);
}

void WorldGenerator::generate(Vec2i origin, Vec2i radius)
{
    place_terrain(origin, radius);
}
