#pragma once

#include "scene_id.hpp"
#include "scene.hpp"

class SceneManager
{
public:
    SceneManager(Window &window, Assets &assets) : m_window(window), m_assets(assets) {}

    void update();

private:
    void create_scene(SceneID scene_id);

private:
    Scene *m_scene = nullptr;
    SceneID m_current_scene = SceneID::Main;

    Window &m_window;
    Assets &m_assets;
};