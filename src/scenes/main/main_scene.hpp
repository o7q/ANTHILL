#pragma once

#include "assets/assets.hpp"
#include "events/event_pool.hpp"
#include "events/external/base.hpp"
#include "px/instance/instance.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"
#include "world_generator/world_generator.hpp"

class MainScene : public Scene
{
  public:
    MainScene(px::Instance &instance, const Assets &assets)
        : Scene(instance), r_assets(assets), m_world({32, 32}), m_generator(m_world, r_assets)
    {
    }

  protected:
    void onStart() override;
    void onTick() override;

    void renderText(std::vector<px::RenderCommand> &renderCommands);

    void handle_events();

    EventPool<ExternalEvent> m_events;

  private:
    const Assets &r_assets;

    World m_world;
    WorldGenerator m_generator;
    Camera m_camera;

    px::Texture m_healthText;
    px::Texture m_energyText;

    px::Texture m_fpsText;
    px::Texture m_entitiesText;
    px::Texture m_chunksText;
};
