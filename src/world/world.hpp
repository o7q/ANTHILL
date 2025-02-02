#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "physics/world_physics.hpp"

#include "../math/segment.hpp"

#include "particle/particle.hpp"
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

    void update();

    void setParticle(int x, int y, Particle particle);

    Particle getParticle(int x, int y);
    Vec2<int> getSize() const { return m_size; }
    const Texture &getWorldTexture() const { return m_world_texture; }
    const std::vector<Segment> &getWorldBounds() const { return m_world_bounds; }

    void drawParticles(int x, int y, int radius, Particle particle, DrawShape drawShape = DrawShape::Circle);
    void drawParticles(int x, int y, int radius, Particle::Preset preset, DrawShape drawShape = DrawShape::Circle);

private:
    void update_bounds();
    void draw_particles(int loc_x, int loc_y, int radius, const Particle particle, DrawShape drawShape = DrawShape::Circle);

    Particle **m_particles = nullptr;
    std::vector<Segment> m_world_bounds;
    Texture m_world_texture;
    WorldPhysics m_world_physics;

    int update_speed = 2;

    Vec2<int> m_size;
};