#pragma once

#include <vector>

#include <SDL3/SDL.h>

#include "particle/particle.hpp"
#include "physics/world_physics.hpp"

#include "../engine/math/vector.hpp"
#include "../engine/math/segment.hpp"
#include "../engine/texture/texture.hpp"


class World
{
public:
    struct Portal
    {
        World *world = nullptr;

        bool up = false;
        bool down = false;
        bool left = false;
        bool right = false;
    };

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

    void setPortal(Portal portal)
    {
        if (portal.world == nullptr)
        {
            return;
        }

        bool horizontal_invalid = portal.world->getSize().x != m_size.x && (portal.up || portal.down);
        bool vertical_invalid = portal.world->getSize().y != m_size.y && (portal.left || portal.right);

        if (horizontal_invalid || vertical_invalid)
        {
            return;
        }

        m_world_physics->set_physics_portal(portal.world->m_world_physics, portal.up, portal.down, portal.left, portal.right);
    }

    void clearPortal()
    {
        m_world_physics->clear_physics_portal();
    }

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

    const int update_speed = 1;

    Vec2<int> m_size;
};