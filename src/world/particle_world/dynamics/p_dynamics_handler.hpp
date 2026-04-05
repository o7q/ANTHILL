#pragma once

#include "utils/data_structures/chunk_map.hpp"
#include "world/particle_world/navmesh/navmesh.hpp"
#include "world/particle_world/particle.hpp"

class PDynamicsHandler
{
  private:
    struct ParticleObject
    {
        Particle *particle = nullptr;
        Vec2i pos;
    };

  public:
    PDynamicsHandler(ChunkMap<Particle> &particles, Navmesh &navmesh)
        : r_particles(particles), r_navmesh(navmesh)
    {
    }

    void update(float dt, Vec2i origin, Vec2i size);

    void setGravity(float gravity) { m_gravity = gravity; }
    void addGravity(float gravity) { m_gravity += gravity; }
    float getGravity() const { return m_gravity; }

    void applyForce(int x, int y, float power, float dt);

  private:
    void update_particle(ParticleObject po, float dt);
    void resolve_particle_collision(ParticleObject po, Vec2f start, Vec2f end,
                                    float dt);
    void finalize_particle(ParticleObject po);

    bool can_solid_occupy(Particle *p);
    bool can_liquid_occupy(Particle *p);
    bool can_gas_occupy(Particle *p);

    void update_sand_particle(ParticleObject po, float dt);
    void update_water_particle(ParticleObject po, float dt);
    void update_smoke_particle(ParticleObject po, float dt);

  private:
    ChunkMap<Particle> &r_particles;
    Navmesh &r_navmesh;
    bool m_updateSwapID = 0;

    float m_gravity = 0.1f;
};
