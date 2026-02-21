#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "particle.hpp"

class ParticleHandler
{
  public:
    ParticleHandler() : m_particleMap(32, 32) {}

  private:
    SparseChunkMap<Particle> m_particleMap;
};
