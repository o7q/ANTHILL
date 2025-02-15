#include "world.hpp"

#include <SDL3/SDL.h>

#include "../engine/math/random.hpp"
#include "../engine/math/bounding_box.hpp"

World::World(SDL_Renderer *renderer,
             unsigned int width,
             unsigned int height) : m_world_texture(renderer, width, height)
{
    m_size.x = width;
    m_size.y = height;

    m_particles = new Particle *[height];

    for (int y = 0; y < m_size.y; ++y)
    {
        m_particles[y] = new Particle[m_size.x];

        for (int x = 0; x < m_size.x; ++x)
        {
            setParticle(x, y, Particle(Particle::Preset::Stone));
        }
    }

    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            if (Random::genInt(0, 10000) == 0)
            {
                drawParticles(x, y, Random::genInt(10, 30), Particle(Particle::Preset::Sand), DrawShape::Circle, false);
            }
            if (Random::genInt(0, 10000) == 0)
            {
                drawParticles(x, y, Random::genInt(3, 20), Particle(Particle::Preset::Water), DrawShape::Circle, false);
            }
            if (Random::genInt(0, 1000) == 0)
            {
                drawParticles(x, y, Random::genInt(6, 30), Particle(Particle::Preset::Steam), DrawShape::Circle, false);
            }
            if (Random::genInt(0, 100000) == 0)
            {
                drawParticles(x, y, Random::genInt(20, 30), Particle(Particle::Preset::Blood), DrawShape::Circle, false);
            }
        }
    }

    m_world_physics = new WorldPhysics(m_particles, &m_world_texture, m_size.x, m_size.y);
    m_world_texture.setOrigin(0, 0);
    m_world_texture.update();
}

World::~World()
{
    if (m_world_physics != nullptr)
    {
        delete m_world_physics;
    }

    for (int y = 0; y < m_size.y; ++y)
    {
        if (m_particles[y] != nullptr)
        {
            delete[] m_particles[y];
        }
    }
    if (m_particles != nullptr)
    {
        delete[] m_particles;
    }
}

void World::update(BoundingBox *box)
{
    BoundingBox locked_bb(m_size.x / 2.0f, m_size.y / 2.0f, m_size.x, m_size.y);

    if (box != nullptr)
    {
        Vec2<int> pos = box->getPosition().toInt() - m_position;
        Vec2<int> size = box->getSize().toInt();
        locked_bb.setPosition(pos.x, pos.y);
        locked_bb.setSize(size.x, size.y);
    }

    m_world_physics->update_particles(&locked_bb);

    generate_world_hitbox(&locked_bb);
    m_world_texture.update();
}