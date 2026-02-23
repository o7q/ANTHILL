#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "world/particle.hpp"

class PDynamicsHandler
{
  private:
    struct ParticleObject
    {
        Particle *particle = nullptr;
        int x = 0, y = 0;
    };

  public:
    PDynamicsHandler(SparseChunkMap<Particle> &particles)
        : r_particles(particles)
    {
    }

    void update(float dt);

  private:
    void update_particle(ParticleObject po, float dt);
    void resolve_particle_collision(ParticleObject po, Vec2<float> start,
                                    Vec2<float> end, float dt);
    void finalize_particle(ParticleObject po);

    void update_sand_particle(ParticleObject po, float dt);
    void update_water_particle(ParticleObject po, float dt);
    void update_smoke_particle(ParticleObject po, float dt);

  private:
    SparseChunkMap<Particle> &r_particles;
    bool m_updateSwapID = 0;
};
