#include "jungle.hpp"

WorldGenerator::JungleGenerator::JungleGenerator(Settings settings) : Generator(settings)
{
    generate_terrain();
}