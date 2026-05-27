#pragma once

#include "core/data_structures/chunk_map.hpp"
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

    void generate(Vec2i origin, Vec2i radius);

  private:
    void generate_place(Vec2i origin, Vec2i radius);
    void generate_place_at_pos(Vec2i pos);

    BiomeID get_biome(Vec2i pos);
    void get_biome_candidates(Vec2i pos, std::vector<Math::Random::WeightedValue<BiomeID>> &candidates);

    PositionalSpawnData generate_desert_layer1(Vec2i pos);
    PositionalSpawnData generate_desert_layer2(Vec2i pos);

  private:
    World &r_world;
    const Assets &r_assets;
    ChunkMap<std::optional<PositionalSpawnData>> m_structureLayer;
    std::unordered_set<Vec2i, Vec2Hash<int>> m_generatedChunkMarkers;

    bool m_structureGenerated = false;

    uint32_t m_seed = 0;
};
