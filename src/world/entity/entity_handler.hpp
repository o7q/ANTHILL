#pragma once

#include "entity/entity.hpp"
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
        for (auto it = m_entities.begin(); it != m_entities.end();)
        {
            std::vector<const Entity *> nearby;

            for (auto &entity : m_entities)
            {
                nearby.push_back(entity.get());
            }

            (*it)->update(dt, nearby);
            if ((*it)->isDead())
            {
                it = m_entities.erase(it);
            }
            else
            {
                it++;
            }
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
        m_latestEntity = entity.get();
        m_entities.push_back(std::move(entity));
    }

    void addPlayer(std::unique_ptr<Player> player)
    {
        m_currentPlayer = player.get();
        m_entities.push_back(std::move(player));
    }

    Player *getCurrentPlayer() { return m_currentPlayer; }
    const Player *getCurrentPlayer() const { return m_currentPlayer; }
    Entity *getLatestEntity() { return m_latestEntity; }
    const Entity *getLatestEntity() const { return m_latestEntity; }

  private:
    Player *m_currentPlayer = nullptr;
    Entity *m_latestEntity = nullptr;
    std::vector<std::unique_ptr<Entity>> m_entities;
};
