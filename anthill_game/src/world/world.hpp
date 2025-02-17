#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "../engine/math/vector.hpp"
#include "../engine/math/segment.hpp"
#include "../engine/texture/texture.hpp"

#include "particle/particle.hpp"

#include "../world_physics/world_physics.hpp"

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

    void update(BoundingBox *box = nullptr);

    void move(int x, int y)
    {
        m_position.x += x;
        m_position.y += y;
        m_world_texture.setPosition(m_position.x, m_position.y);
    }

    void setPosition(int x, int y)
    {
        m_position.x = x;
        m_position.y = y;
        m_world_texture.setPosition(x, y);
    }

    WorldPhysics *getWorldPhysics() const { return m_world_physics; }

    void setParticle(int x, int y, Particle particle, bool is_global_coordinate = true);
    void drawParticles(int loc_x, int loc_y, int radius, const Particle particle, DrawShape drawShape = DrawShape::Circle, bool is_global_coordinate = true);

    Particle getParticle(int x, int y, bool is_global_coordinate = true) const;
    Vec2<int> getPosition() const { return m_position; }
    Vec2<int> getSize() const { return m_size; }
    const Texture &getWorldTexture() const { return m_world_texture; }
    const std::vector<Segment> &getWorldHitbox() const { return m_world_hitbox; }

private:
    void generate_world_hitbox(BoundingBox *box = nullptr);

    Vec2<int> m_position;

    Particle **m_particles = nullptr;
    WorldPhysics *m_world_physics = nullptr;
    std::vector<Segment> m_world_hitbox;
    Texture m_world_texture;

    const bool m_debug_render_solid_collision = false;

    Vec2<int> m_size;
};