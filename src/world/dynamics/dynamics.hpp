#pragma once

#include "engine/sparse_chunk_map.hpp"
#include "engine/verlet.hpp"
#include "world/particle.hpp"
#include <iostream>

class ParticleDynamics
{
  private:
    struct ParticleSubject
    {
        Particle particle;
        int x = 0, y = 0;
    };

  public:
    ParticleDynamics(SparseChunkMap<Particle> &particles)
        : r_particles(particles)
    {
    }

    void update(float dt)
    {
        const Vec2<unsigned int> chunkSize = r_particles.getChunkSize();
        for (auto &[chunkPos, chunk] : r_particles.getChunks())
        {
            for (int y = chunkSize.y - 1; y >= 0; --y)
            {
                for (int x = chunkSize.x - 1; x >= 0; --x)
                {
                    int px = chunkPos.first * chunkSize.x + x;
                    int py = chunkPos.second * chunkSize.y + y;

                    ParticleSubject p;
                    p.particle = r_particles.get(px, py);
                    p.x = px;
                    p.y = py;

                    update_particle(p, dt);
                }
            }
        }
    }

  private:
    void update_particle(ParticleSubject p, float dt) { particle_move(p, dt); }

    void particle_move(ParticleSubject p, float dt)
    {
        

        // if (p.particle.getVerlet().areForcesApplied())
        // {
        //     particle_move_verlet(p, dt);
        // }
        // else
        // {
        //     particle_move_simple(p);
        // }
    }

    void particle_move_verlet(ParticleSubject p, float dt)
    {
        p.particle.getVerlet().update(dt);
        r_particles.move(Vec2<int>(p.x, p.y),
                         Vec2<int>(p.particle.getVerlet().getPosition().x,
                                   p.particle.getVerlet().getPosition().y));
    }

    void particle_move_simple(ParticleSubject p)
    {
        switch (p.particle.getPhysicsType())
        {
        case Particle::PhysicsType::Sand:
            particle_move_simple_sand(p);
            break;
        default:
            break;
        }
    }

    void particle_move_simple_sand(ParticleSubject p)
    {
        if (r_particles.get(p.x, p.y + 1).getMatterType() ==
            Particle::MatterType::Gas)
        {
            r_particles.move(Vec2<int>(p.x, p.y), Vec2<int>(p.x, p.y + 1));
        }
    }

  private:
    SparseChunkMap<Particle> &r_particles;
};
