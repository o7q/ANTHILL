#include "scene_main.hpp"

#include "../engine/logger/logger.hpp"

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Level::Info, "MainScene", "Init");
        m_window.setCursor(m_assets.surfaces.crosshair_2x);
    }

    if (update())
    {
        update_input();

        update_world();
        update_player();

        update_bullets();

        update_render();
        update_hud();
    }

    return SceneID::Main;
}