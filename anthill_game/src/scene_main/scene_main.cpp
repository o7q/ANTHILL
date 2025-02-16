#include "scene_main.hpp"

#include "../engine/logger/logger.hpp"

#include <iostream>

SceneID MainScene::run()
{
    if (init())
    {
        Log::log(Log::Type::Info, "MainScene", "Init");
        m_window.setCursor(m_assets.images.crosshair_2x.getSDLSurface());
    }

    if (update())
    {
        update_input();

        update_world();
        update_entities();
        update_player();
        m_bullet_manager.update(DT);
        update_render();
        update_hud();
        std::cout << m_bullet_manager.getBullets().size() << std::endl;
    }

    return SceneID::Main;
}