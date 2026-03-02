#pragma once

#include "backend/viewport.hpp"
#include "camera/camera.hpp"
#include "world/particle_handler.hpp"

class World
{
  public:
    World() = default;
    World(const World &other) = delete;
    World &operator=(const World &other) = delete;

    void render(Viewport &viewport, const Camera &camera);

    ParticleHandler &getParticleHandler() { return m_particleHandler; }

  private:
    ParticleHandler m_particleHandler;
};
