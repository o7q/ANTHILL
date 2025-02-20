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

    World(unsigned int width, unsigned int height);
    ~World();

    void update(BoundingBox *box = nullptr);

    void setParticle(int x, int y, Particle particle, bool is_global_coordinate = false);
    void drawParticles(int loc_x, int loc_y, int radius, const Particle particle, DrawShape drawShape = DrawShape::Circle, bool is_global_coordinate = false);

    void move(int x, int y);
    void setPosition(int x, int y);

    void primeWorldTexture(SDL_Renderer *renderer);

    Particle getParticle(int x, int y, bool is_global_coordinate = true) const;
    Vec2<int> getPosition() const { return m_position; }
    Vec2<int> getSize() const { return m_size; }

    WorldPhysics *getWorldPhysics() const { return m_world_physics; }
    const Texture *getWorldTexture() const { return m_world_texture; }
    const std::vector<Segment> &getWorldHitbox() const { return m_world_hitbox; }

private:
    void generate_world_hitbox(BoundingBox *box = nullptr);

    Vec2<int> m_position;

    Particle **m_particles = nullptr;
    WorldPhysics *m_world_physics = nullptr;
    Texture *m_world_texture = nullptr;

    std::vector<Segment> m_world_hitbox;

    const bool m_debug_render_solid_collision = false;

    Vec2<int> m_size;
};