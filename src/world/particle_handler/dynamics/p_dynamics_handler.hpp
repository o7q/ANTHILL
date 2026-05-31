#pragma once

#include "core/data_structures/chunk_map.hpp"
#include "core/time/time_handler.hpp"
#include "world/particle_handler/navmesh/navmesh.hpp"
#include "world/particle_handler/particle.hpp"
#include <cstdint>

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
        : r_particles(particles), r_navmesh(navmesh), m_swapStates({32, 32})
    {
    }

    void update(TimeHandler::Info timeInfo, Vec2i origin);

    void setGravity(float gravity) { m_gravity = gravity; }
    void addGravity(float gravity) { m_gravity += gravity; }
    float getGravity() const { return m_gravity; }

    void applyForce(Vec2i origin, int radius, float power);

  private:
    void update_particle(ParticleObject po, float dt);
    void handle_particle_trajectory(ParticleObject po, Vec2f start, Vec2f end, float dt);
    void resolve_particle_collision_against_other(ParticleObject po, Particle *hitParticle,
                                                  Vec2i currentCheck, Vec2i previousCheck, float dt);
    void resolve_particle_collision_against_null(ParticleObject po, Vec2i previousCheck);
    void finalize_particle(ParticleObject po);

    bool can_solid_occupy(const Particle *p);
    bool can_liquid_occupy(const Particle *p);
    bool can_gas_occupy(const Particle *p);

    void update_sand_particle(ParticleObject po, float dt);
    void update_sandstone_particle(ParticleObject po, float dt);
    void update_water_particle(ParticleObject po, float dt);
    void update_smoke_particle(ParticleObject po, float dt);

  private:
    ChunkMap<Particle> &r_particles;
    Navmesh &r_navmesh;
    ChunkMap<uint8_t> m_swapStates;
    uint8_t m_globalSwapState = 0;

    float m_gravity = 0.1f;

    const Vec2i m_updateSize = {280 + 50, 210 + 50};
};
