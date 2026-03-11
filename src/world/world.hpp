#pragma once

#include "backend/viewport.hpp"
#include "world/camera/camera.hpp"
#include "world/entity/entity_handler.hpp"
#include "world/particle/particle_handler.hpp"

class World
{
  public:
    World() = default;
    World(const World &other) = delete;
    World &operator=(const World &other) = delete;

    void update(float dt);
    void render(Viewport &viewport);

    ParticleHandler &getParticleHandler() { return m_particleHandler; }
    EntityHandler &getEntityHandler() { return m_entityHandler; }

    Camera &getCamera() { return m_camera; }

  private:
    ParticleHandler m_particleHandler;
    EntityHandler m_entityHandler;

    Camera m_camera;
};
