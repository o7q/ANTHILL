#include "world_generator.hpp"

#include "px/data_structures/chunk_map.hpp"
#include "px/math/random.hpp"
#include "world_generator/spawn_data.hpp"

WorldGenerator::WorldGenerator(World &world, const Assets &assets)
    : r_world(world), r_assets(assets), m_structureLayer({32, 32})
{
    m_seed = Math::Random::unseededRandomInt(0, 1000000);
}
