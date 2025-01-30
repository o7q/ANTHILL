#pragma once

#include <SDL3/SDL.h>

#include "world_physics.hpp"

#include "particle.hpp"
#include "../texture/texture.hpp"
#include "../math/vector.hpp"

class World
{
public:
    World(SDL_Renderer *renderer, unsigned int width, unsigned int height);
    ~World();

    void setParticle(int x, int y, Particle particle);
    Particle getParticle(int x, int y);

    void update();

    const Texture &getWorldTexture() const { return m_world_texture; }
    Vec2<int> getSize() const { return m_size; }

private:
    Particle **m_particles = nullptr;
    Texture m_world_texture;
    WorldPhysics m_world_physics;

    Vec2<int> m_size;
};