#include "backend/logger/logger.hpp"
#include "game.hpp"
#include "identifiers/scene.hpp"
#include "scenes/main/main_scene.hpp"
#include "utils/variant_bp.hpp"
#include <variant>

void Game::update_loop()
{
    if (!m_scene)
    {
        return;
    }

    m_scene->update();

    Scene::Result result = m_scene->getResult();

    if (!result.shouldLoadScene)
    {
        return;
    }

    std::visit(overloaded{[&](SceneID id)
                          {
                              switch (id)
                              {
                              case SceneID::Main:
                                  m_scene = std::make_unique<MainScene>(m_assets, m_window);
                                  break;
                              default:
                                  break;
                              }
                          },
                          [](const std::string &id)
                          { Logger::info("Game::update_loop()", "Recieved custom scene change: " + id); }},
               result.sceneLoadID);
}
