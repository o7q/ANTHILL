#pragma once

#include "math/random.hpp"
#include "utils/data_structures/index_2d.hpp"
#include "world/particle_world/particle_world.hpp"

class Generator
{
  public:
    Generator(ParticleWorld &world) : r_world(world)
    {
        m_seed = Math::Random::weakRandInt(0, 10000000);
    }

    void generate(Vec2i origin) { generate_terrain(origin); }

  private:
    void generate_terrain(Vec2i origin);
    void generate_terrain_at_pos(Vec2i pos);

  private:
    ParticleWorld &r_world;
    std::vector<Index2D> m_generatedChunkMarkers;

    uint32_t m_seed = 0;

    Vec2i m_generateRadius = {10, 10};
    Vec2i m_biomeSize = {200, 200};
};
