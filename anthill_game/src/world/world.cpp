#include "world.hpp"

#include <SDL3/SDL.h>

#include "../engine/math/random.hpp"
#include "../engine/math/bounding_box.hpp"

World::World(unsigned int width,
             unsigned int height)
{
    m_size.x = width;
    m_size.y = height;

    m_particles = new Particle *[height];

    for (int y = 0; y < m_size.y; ++y)
    {
        m_particles[y] = new Particle[m_size.x];

        for (int x = 0; x < m_size.x; ++x)
        {
            setParticle(x, y, Particle(Particle::Preset::Air));
        }
    }

    m_world_physics = new WorldPhysics(m_particles, m_size.x, m_size.y);
}

World::~World()
{
    if (m_world_physics != nullptr)
    {
        delete m_world_physics;
    }

    if (m_world_texture != nullptr)
    {
        delete m_world_texture;
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

void World::update(float dt, BoundingBox *box)
{
    BoundingBox update_bb(m_size.x / 2.0f, m_size.y / 2.0f, m_size.x, m_size.y);

    if (box != nullptr)
    {
        Vec2<int> pos = box->getPosition().toInt() - m_position;
        Vec2<int> size = box->getSize().toInt();
        update_bb.setPosition(pos.x, pos.y);
        update_bb.setSize(size.x, size.y);
    }

    const float speed = 2.0f;
    const float time_step = 1.0f / speed;

    m_remaining_time += dt;

    while (m_remaining_time >= time_step)
    {
        m_world_physics->updateParticles(&update_bb);
        m_remaining_time -= time_step;
    }

    generate_world_hitbox(&update_bb);

    if (m_world_texture != nullptr)
    {
        if (m_debug_render_solid_collision)
            for (int y = 0; y < m_size.y; ++y)
                for (int x = 0; x < m_size.x; ++x)
                    m_world_texture->setPixel(x, y, m_particles[y][x].solid_enable_collision ? m_particles[y][x].color.hex() : 0xFF0000FF);

        m_world_texture->update();
    }
}

void World::move(int x, int y)
{
    m_position.x += x;
    m_position.y += y;

    if (m_world_texture != nullptr)
    {
        m_world_texture->setPosition(m_position.x, m_position.y);
    }
}

void World::setPosition(int x, int y)
{
    m_position.x = x;
    m_position.y = y;

    if (m_world_texture != nullptr)
    {
        m_world_texture->setPosition(x, y);
    }
}

void World::primeWorldTexture(SDL_Renderer *renderer)
{
    m_world_texture = new Texture(renderer, m_size.x, m_size.y);
    m_world_texture->setPosition(m_position.x, m_position.y);
    m_world_texture->setOrigin(0, 0);

    for (int y = 0; y < m_size.y; ++y)
    {
        for (int x = 0; x < m_size.x; ++x)
        {
            m_world_texture->setPixel(x, y, m_particles[y][x].color.hex());
        }
    }

    m_world_texture->update();
    m_world_physics->setWorldTexture(m_world_texture);
}