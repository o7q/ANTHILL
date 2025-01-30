#pragma once

#include <algorithm>

#include <SDL3/SDL.h>

#include "world_physics.hpp"

#include "particle.hpp"
#include "../texture/texture.hpp"
#include "../math/vector.hpp"

class World
{
public:
    enum class DrawShape
    {
        Circle,
        Square
    };

    World(SDL_Renderer *renderer, unsigned int width, unsigned int height);
    ~World();

    void setParticle(int x, int y, Particle particle);
    Particle getParticle(int x, int y);

    void update();

    const Texture &getWorldTexture() const { return m_world_texture; }
    Vec2<int> getSize() const { return m_size; }

    void drawParticles(int x, int y, int radius, Particle particle, DrawShape drawShape = DrawShape::Circle)
    {
        const Particle draw_particle = particle;
        draw_particles(x, y, radius, draw_particle, drawShape);
    }
    void drawParticles(int x, int y, int radius, Particle::Preset preset, DrawShape drawShape = DrawShape::Circle)
    {
        const Particle draw_particle = Particle(preset);
        draw_particles(x, y, radius, draw_particle, drawShape);
    }

private:
    void draw_particles(int loc_x, int loc_y, int radius, const Particle particle, DrawShape drawShape = DrawShape::Circle)
    {
        switch (drawShape)
        {
        case DrawShape::Square:
            for (int y = 0; y < radius; ++y)
            {
                for (int x = 0; x < radius; ++x)
                {
                    int x_clamped = std::clamp(loc_x + x - radius / 2, 0, m_size.x - 1);
                    int y_clamped = std::clamp(loc_y + y - radius / 2, 0, m_size.y - 1);

                    setParticle(x_clamped, y_clamped, particle);
                }
            }
            break;
        case DrawShape::Circle:
            for (int y = loc_y - radius; y <= loc_y + radius; ++y)
            {
                for (int x = loc_x - radius; x <= loc_x + radius; ++x)
                {
                    if ((x - loc_x) * (x - loc_x) + (y - loc_y) * (y - loc_y) <= radius * radius)
                    {
                        int x_clamped = std::clamp(x, 0, m_size.x - 1);
                        int y_clamped = std::clamp(y, 0, m_size.y - 1);

                        setParticle(x_clamped, y_clamped, particle);
                    }
                }
            }
            break;
        }
    }

    Particle **m_particles = nullptr;
    Texture m_world_texture;
    WorldPhysics m_world_physics;

    Vec2<int> m_size;
};