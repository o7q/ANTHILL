#pragma once

#include <algorithm>
#include <vector>

#include <SDL3/SDL.h>

#include "world_physics.hpp"

#include "particle.hpp"
#include "../texture/texture.hpp"
#include "../math/vector.hpp"
#include "../bounding_box/bounding_box.hpp"

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

    const std::vector<BoundingBox> &getWorldBounds() const { return m_world_bounds; }

private:
    void draw_particles(int loc_x, int loc_y, int radius, const Particle particle, DrawShape drawShape = DrawShape::Circle);

    Particle **m_particles = nullptr;
    Texture m_world_texture;
    WorldPhysics m_world_physics;
    std::vector<BoundingBox> m_world_bounds;

    Vec2<int> m_size;
};