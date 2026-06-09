#pragma once

#include "assets/assets.hpp"
#include "events/event_pool.hpp"
#include "events/external/base.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"
#include "world_generator/world_generator.hpp"

class MainScene : public Scene
{
  public:
    MainScene(Window &window, const Assets &assets)
        : Scene(window), r_assets(assets), m_world({32, 32}), m_generator(m_world, r_assets)
    {
    }

  protected:
    void onStart() override;
    void onTick() override;

    void renderText(std::vector<RenderCommand> &renderCommands);

    void handle_events();

    EventPool<ExternalEvent> m_events;

  private:
    const Assets &r_assets;

    World m_world;
    WorldGenerator m_generator;
    Camera m_camera;

    Texture m_healthText;
    Texture m_energyText;

    Texture m_fpsText;
    Texture m_entitiesText;
    Texture m_chunksText;
};
