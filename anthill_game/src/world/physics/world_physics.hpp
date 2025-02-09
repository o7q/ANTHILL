#pragma once

#include "../particle/particle.hpp"
#include "../../texture/texture.hpp"
#include "../../math/bounding_box.hpp"

class WorldPhysics
{
public:
    void init(Particle **particles,
              Texture *world_texture,
              unsigned int width,
              unsigned int height)
    {
        m_particles = particles;
        m_world_texture = world_texture;
        m_size.x = width;
        m_size.y = height;
    }

    void update_particles(BoundingBox *box = nullptr);

private:
    // shorthand operations (unsafe, no out of bounds checking)
    void p_set(int x, int y, Particle particle);
    void p_swap(int x1, int y1, int x2, int y2);
    void p_move(int x1, int y1, int x2, int y2);
    Color p_mix(Color a, Color b, float mult_a = 1.0f, float mult_b = 1.0f, float div = 2.0f, bool mix_alpha = true);
    Particle p_get(int x, int y);
    //

    bool in_bounds(int x, int y);

private:
    void update_particle(int x, int y);

    void update_sand(Particle particle, int x, int y);
    void update_water(Particle particle, int x, int y);
    void update_smoke(Particle particle, int x, int y);
    void update_goop(Particle particle, int x, int y);

private:
    Particle **m_particles = nullptr;
    Texture *m_world_texture = nullptr;
    Vec2<int> m_size;
};