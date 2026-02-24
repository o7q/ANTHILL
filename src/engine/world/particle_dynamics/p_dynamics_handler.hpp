#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "engine/world/particle.hpp"

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

    void setGravity(float gravity) { m_gravity = gravity; }
    void addGravity(float gravity) { m_gravity += gravity; }
    float getGravity() const { return m_gravity; }
    void setUpdateInfo(int originX, int originY, int chunk_radius_to_update)
    {
        m_updateChunksOrigin = Vec2<int>(originX, originY);
        m_updateChunksRadius = chunk_radius_to_update;
    }

  private:
    void update_particle(ParticleObject po, float dt);
    void resolve_particle_collision(ParticleObject po, Vec2<float> start,
                                    Vec2<float> end, float dt);
    void finalize_particle(ParticleObject po);

    bool can_solid_occupy(Particle *p);
    bool can_liquid_occupy(Particle *p);
    bool can_gas_occupy(Particle *p);

    void update_sand_particle(ParticleObject po, float dt);
    void update_water_particle(ParticleObject po, float dt);
    void update_smoke_particle(ParticleObject po, float dt);

  private:
    SparseChunkMap<Particle> &r_particles;
    bool m_updateSwapID = 0;

    float m_gravity = 0.1f;
    Vec2<int> m_updateChunksOrigin;
    int m_updateChunksRadius = 4;
};
