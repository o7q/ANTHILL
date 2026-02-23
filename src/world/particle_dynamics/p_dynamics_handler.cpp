#include "p_dynamics_handler.hpp"
#include "engine/verlet.hpp"
#include <iostream>

void PDynamicsHandler::update(float dt)
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

                if (Particle *p = r_particles.get(px, py))
                {
                    if (p->getUpdateSwapID() == m_updateSwapID || p->isAir())
                    {
                        continue;
                    }

                    ParticleSubject ps;
                    ps.particle = p;
                    ps.x = px;
                    ps.y = py;
                    update_particle(ps, dt);
                }
            }
        }
    }

    m_updateSwapID = !m_updateSwapID;
}

void PDynamicsHandler::update_particle(ParticleSubject ps, float dt)
{
    switch (ps.particle->getPhysicsType())
    {
    case Particle::PhysicsType::Sand:
        update_sand_particle(ps, dt);
        break;
    case Particle::PhysicsType::Water:
        update_water_particle(ps, dt);
        break;
    default:
        break;
    }
}

void PDynamicsHandler::resolve_particle_collision(ParticleSubject ps,
                                                  Vec2<float> start,
                                                  Vec2<float> end, float dt)
{
    Vec2<int> previousCheck{};
    Vec2<int> hitCell{};
    bool hit = false;

    auto function = [&](int x, int y)
    {
        if (Particle *next = r_particles.get(x, y))
        {
            if (!next->isAir() && next != ps.particle)
            {
                hit = true;
                hitCell = Vec2<int>(x, y);
                return false;
            }
        }

        previousCheck = Vec2<int>(x, y);
        return true;
    };
    MathUtils::bresenhamLine(Vec2<int>(start.x, start.y),
                             Vec2<int>(end.x, end.y), function);

    if (!hit)
    {
        return;
    }

    VerletBody &verlet = ps.particle->getVerlet();

    Vec2<int> hitDirection = hitCell - previousCheck;

    Vec2<float> vel = verlet.getVelocity(dt);
    Vec2<float> newVel = vel;

    if (hitDirection.x != 0)
    {
        newVel.x = -vel.x;
    }

    if (hitDirection.y != 0)
    {
        newVel.y = -vel.y;
    }

    newVel.x *= 0.1f;
    newVel.y *= 0.1f;

    if (std::abs(newVel.x) < 0.1f)
    {
        newVel.x = 0;
    }
    if (std::abs(newVel.y) < 0.1f)
    {
        newVel.y = 0;
    }

    verlet.setPosition(previousCheck.x, previousCheck.y);
    verlet.setVelocity(newVel.x, newVel.y, dt);
}

void PDynamicsHandler::move_particle(ParticleSubject ps)
{
    Vec2<float> finalPos = ps.particle->getVerlet().getPosition();

    int newX = static_cast<int>(std::trunc(finalPos.x));
    int newY = static_cast<int>(std::trunc(finalPos.y));

    ps.particle->setUpdateSwapID(m_updateSwapID);
    r_particles.move(ps.x, ps.y, newX, newY);
}
