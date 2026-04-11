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

    void generateInRadius(Vec2i origin, Vec2u size);

  private:
    ParticleWorld &r_world;
    std::vector<Index2D> m_generatedChunkMarkers;

    uint32_t m_seed = 0;
};
