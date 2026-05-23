#pragma once

#include "assets/assets.hpp"
#include "scene/scene.hpp"
#include "world/world.hpp"
#include "world_dungeon/dungeon_generator.hpp"

class MainScene : public Scene
{
  public:
    MainScene(Window &window, const Assets &assets) : Scene(window, assets) {}

  protected:
    void onStart() override;
    void onTick() override;

    void renderText(std::vector<RenderCommand> &renderCommands);

  private:
    World m_world;
    Camera m_camera;

    DungeonGenerator m_dungeonGenerator;

    Texture m_healthText;
    Texture m_energyText;

    Texture m_fpsText;
    Texture m_entitiesText;
    Texture m_chunksText;
};
