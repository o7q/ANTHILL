#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "engine/verlet.hpp"
#include "world/particle.hpp"
#include <cmath>

class PDynamicsHandler
{
  private:
    struct ParticleSubject
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
    void update_particle(ParticleSubject ps, float dt);
    void resolve_particle_collision(ParticleSubject ps, Vec2<float> start,
                                    Vec2<float> end, float dt);
    void move_particle(ParticleSubject ps);

    void update_sand_particle(ParticleSubject ps, float dt);
    void update_water_particle(ParticleSubject ps, float dt);

  private:
    SparseChunkMap<Particle> &r_particles;
    bool m_updateSwapID = 0;
};
