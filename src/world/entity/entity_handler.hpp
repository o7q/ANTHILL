#pragma once

#include "entity/base/entity.hpp"
#include "player/player.hpp"
#include <memory>
#include <vector>

class EntityHandler
{
  public:
    EntityHandler() = default;
    EntityHandler(const EntityHandler &other) = delete;
    EntityHandler &operator=(const EntityHandler &other) = delete;

    void update(float dt)
    {
        for (std::unique_ptr<Entity> &entity : m_entities)
        {
            if (!entity)
            {
                continue;
            }

            entity->update(dt);
        }
    }

    void render(Viewport &viewport, const Camera &camera)
    {
        for (std::unique_ptr<Entity> &entity : m_entities)
        {
            if (!entity)
            {
                continue;
            }

            entity->render(viewport, camera);
        }
    }

    void addEntity(std::unique_ptr<Entity> entity)
    {
        m_entities.push_back(std::move(entity));
    }

    void addPlayer(std::unique_ptr<Player> player)
    {
        m_currentPlayer = player.get();
        m_entities.push_back(std::move(player));
    }

    Player *getCurrentPlayer() { return m_currentPlayer; }

  private:
    Player *m_currentPlayer = nullptr;
    std::vector<std::unique_ptr<Entity>> m_entities;
};
