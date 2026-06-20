#pragma once

#include "px/data_structures/chunk_map.hpp"
#include "world/world.hpp"
#include "world_generator/spawn_data.hpp"
#include <unordered_set>

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

    void generate(px::Vec2i origin, px::Vec2i radius);

  private:
    void generate_prepare_structures();
    void generate_set_in_world(px::Vec2i origin, px::Vec2i radius);
    void generate_set_in_world_at_pos(px::Vec2i pos);

    BiomeID get_biome(px::Vec2i pos);
    void get_biome_candidates(px::Vec2i pos,
                              std::vector<px::Utils::Random::WeightedValue<BiomeID>> &candidates);

    PositionalSpawnData generate_desert_layer1(px::Vec2i pos);
    PositionalSpawnData generate_desert_layer2(px::Vec2i pos);

  private:
    World &r_world;
    const Assets &r_assets;
    px::ChunkMap<StructurePositionalSpawnData> m_structureLayer;
    std::unordered_set<px::Vec2i, px::Vec2Hash<int>> m_generatedChunkMarkers;

    bool m_structureGenerated = false;

    uint32_t m_seed = 0;
};
