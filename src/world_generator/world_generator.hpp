#pragma once

#include "utils/data_structures/index_2d.hpp"
#include "world/world.hpp"

class WorldGenerator
{
  public:
    WorldGenerator(World &world);

    void generate(Vec2i origin) { generate_terrain(origin); }

  private:
    void generate_terrain(Vec2i origin);
    void generate_terrain_at_pos(Vec2i pos);

  private:
    World &r_world;
    std::vector<Index2D> m_generatedChunkMarkers;

    uint32_t m_seed = 0;

    Vec2i m_generateRadius = {10, 10};
    Vec2i m_biomeSize = {200, 200};
};
