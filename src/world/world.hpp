#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "world/entity/entity_handler.hpp"
#include "world/particle/particle_handler.hpp"

class World
{
  public:
    World() = default;
    World(const World &other) = delete;
    World &operator=(const World &other) = delete;

    void update(float dt);
    void render(Viewport &viewport, const Camera &camera);

    ParticleHandler &getParticleHandler() { return m_particleHandler; }
    EntityHandler &getEntityHandler() { return m_entityHandler; }

  private:
    ParticleHandler m_particleHandler;
    EntityHandler m_entityHandler;
};
