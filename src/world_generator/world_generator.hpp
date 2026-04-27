#pragma once

#include "utils/data_structures/index_2d.hpp"
#include "world/world.hpp"

class WorldGenerator
{
  private:
    struct BiomeWeight
    {
        BiomeID id = BiomeID::Void;
        int weight = 1;
    };

  public:
    WorldGenerator(World &world, const Assets &assets);

    void generate(Vec2i origin, Vec2i radius);

  private:
    void place_terrain(Vec2i origin, Vec2i radius);

    BiomeID get_biome(Vec2i pos);
    void get_biome_candidates(Vec2i pos, std::vector<BiomeWeight> &candidates);

  private:
    World &r_world;
    const Assets &r_assets;
    std::vector<Index2D> m_generatedChunkMarkers;

    uint32_t m_seed = 0;
};
