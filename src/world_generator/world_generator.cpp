#include "world_generator.hpp"
#include "math/random.hpp"

WorldGenerator::WorldGenerator(World &world) : r_world(world)
{
    m_seed = Math::Random::weakRandInt(0, 10000000);
}
