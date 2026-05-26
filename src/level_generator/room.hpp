#pragma once

#include "core/math/geometry/rectangle.hpp"
#include "core/math/geometry/vec.hpp"
#include "world/particle_handler/particle.hpp"
#include "world_generator/generate_result.hpp"
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Entity;

class Room
{
  public:
    Room() = default;

    Vec2i getSize() const { return m_size; }
    const std::unordered_map<Vec2i, Particle, Vec2Hash<int>> &getParticles() const { return m_particles; }
    const std::unordered_map<Vec2i, Color, Vec2Hash<int>> &getBackground() const { return m_background; }
    const std::unordered_map<RectangleSide, int> &getConnectionPoints() const { return m_connectionPoints; }
    const std::unordered_map<Vec2i, std::vector<std::unique_ptr<Entity>>, Vec2Hash<int>>
    createEntities() const;

  protected:
    struct InitConfig
    {
        std::string backgroundPath     = "";
        std::string particleColorPath  = "";
        std::string particleLookupPath = "";
    };

    void init(InitConfig config);
    void init(Vec2i size) { m_size = size; }

    std::unordered_map<Vec2i, Particle, Vec2Hash<int>> m_particles;
    std::unordered_map<Vec2i, Color, Vec2Hash<int>> m_background;
    std::unordered_map<RectangleSide, int> m_connectionPoints;

  private:
    Vec2i m_size;
};
