#pragma once

#include "particle.hpp"
#include "../texture/texture.hpp"

#include "../types.hpp"

class World
{
public:
    World(SDL_Renderer *renderer, unsigned int width, unsigned int height);
    ~World();

    void setParticle(unsigned int x, unsigned int y, Particle particle);

    void update();

    const Texture &getWorldTexture() const { return m_world_texture; }
    Vec2<unsigned int> getSize() const { return m_size; }

private:
    Particle **m_particles = nullptr;
    Texture m_world_texture;

    Vec2<unsigned int> m_size;
};