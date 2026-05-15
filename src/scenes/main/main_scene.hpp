#pragma once

#include "assets/assets.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"
#include "world_generator/world_generator.hpp"
#include <string>
#include <unordered_map>

class MainScene : public Scene
{
  public:
    MainScene(Window &window, const Assets &assets) : Scene(window, assets), m_generator(m_world, r_assets) {}

  protected:
    void onStart() override;
    void onTick() override;

    void renderText(std::vector<RenderCommand> &renderCommands);

  private:
    World m_world;
    WorldGenerator m_generator;
    Camera m_camera;

    Texture m_healthText;
    Texture m_energyText;
    
    Texture m_fpsText;
    Texture m_entitiesText;
    Texture m_chunksText;
};
