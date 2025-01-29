#pragma once

#include <SDL3/SDL.h>

#include "particle.hpp"
#include "../texture/texture.hpp"
#include "../math/vector.hpp"

class World
{
public:
    World(SDL_Renderer *renderer, unsigned int width, unsigned int height);
    ~World();

    void setParticle(int x, int y, Particle particle);

    void update();

    const Texture &getWorldTexture() const { return m_world_texture; }
    Vec2<int> getSize() const { return m_size; }

private:
    void update_particles();
    void update_particle(int x, int y);

    void update_sand(Particle particle, int x, int y);
    void update_water(Particle particle, int x, int y);

    void swap_particle(int x1, int y1, int x2, int y2)
    {
        Particle temp = m_particles[y2][x2];
        setParticle(x2, y2, m_particles[y1][x1]);
        setParticle(x1, y1, temp);
    }

private:
    Particle **m_particles = nullptr;
    Texture m_world_texture;

    Vec2<int> m_size;
};