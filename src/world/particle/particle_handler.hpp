#pragma once

#include "backend/texture/texture.hpp"
#include "backend/viewport/viewport.hpp"
#include "utils/data_structures/chunk_map.hpp"
#include "world/camera/camera.hpp"
#include "world/particle/particle.hpp"
#include "world/particle/particle_dynamics/p_dynamics_handler.hpp"

class ParticleHandler
{
  public:
    ParticleHandler() : m_particles(32, 32), m_pDynamicsHandler(m_particles) {}

    void update(float dt) { m_pDynamicsHandler.update(dt); }

    void set(int x, int y, Particle p);
    void draw(int x, int y, Particle p, int radius = 5);

    void textureToParticles(const Texture &texture, Vec2<int> pos, Particle p)
    {
        Vec2<int> size = texture.getSize().toInt();
        Vec2<int> halfSize = texture.getSize().toInt() / 2;

        for (int y = 0; y < size.y; ++y)
        {
            for (int x = 0; x < size.x; ++x)
            {
                Color col = texture.getPixel(x, y);
                p.setColor(col);

                set(pos.x + static_cast<int>(x) - halfSize.x,
                    pos.y + static_cast<int>(y) - halfSize.y, p);
            }
        }
    }

    template <typename QueryFunction>
    void query(Vec2<int> start, Vec2<int> end, QueryFunction &&query,
               bool skipNull = true) const
    {
        for (int y = start.y; y <= end.y; ++y)
        {
            for (int x = start.x; x <= end.x; ++x)
            {
                const Particle *p = m_particles.get(x, y);

                if (!p && skipNull)
                {
                    continue;
                }

                if (query(p))
                {
                    return;
                }
            }
        }
    }

    void render(Viewport &viewport, const Camera &camera)
    {
        Vec2<unsigned int> viewport_size = viewport.getSize();

        for (unsigned int y = 0; y < viewport_size.y; ++y)
        {
            for (unsigned int x = 0; x < viewport_size.x; ++x)
            {
                Vec2<int> pp = camera.viewportToWorld(x, y, viewport);

                if (Particle *p = m_particles.get(pp.x, pp.y))
                {
                    Color pixel = p->getColor();
                    if (!p->isAir())
                    {
                        viewport.setPixel(x, y, pixel);
                    }
                }
            }
        }
    }

    ChunkMap<Particle> &getParticles() { return m_particles; }
    const ChunkMap<Particle> &getParticles() const { return m_particles; }
    PDynamicsHandler &getDynamics() { return m_pDynamicsHandler; }

  private:
    ChunkMap<Particle> m_particles;
    PDynamicsHandler m_pDynamicsHandler;
};
