#pragma once

#include "assets/assets.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"
#include "world_generator/world_generator.hpp"

class MainScene : public Scene
{
  public:
    MainScene(const Assets &assets, Window &window)
        : Scene(assets, window), m_generator(m_world)
    {
    }

  protected:
    void onStart() override;
    void onTick() override;

    void renderText(std::vector<RenderCommand> &renderCommands);

  private:
    World m_world;
    WorldGenerator m_generator;
    Camera m_camera;

    Texture healthText;
    Texture fpsText;
    Texture entitiesText;
    Texture chunksText;
};
