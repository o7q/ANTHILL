#pragma once

#include "camera/camera.hpp"
#include "entity/player/player.hpp"
#include "scene/scene.hpp"
#include "utils/math/random.hpp"
#include "world/world.hpp"
#include <optional>

class TestScene : public Scene
{
  public:
    TestScene(Window &window)
        : Scene(window), m_camera(window.getViewport().getSize())
    {
    }

    std::optional<SceneID> update() override
    {
        if (start())
        {
            
            m_player = std::make_unique<Player>(m_world);
        }
        
        if (tick())
        {
            m_world.getParticleHandler().getDynamics().setUpdateInfo(
                m_camera.getPosition().x, m_camera.getPosition().y, 10);
            Vec2<float> mousePos = r_input.getMousePosition();
            Vec2<int> viewportMousePos =
                r_viewport.windowToViewportPosition(mousePos);

            Vec2<int> worldPos = m_camera.viewportToWorld(viewportMousePos.x,
                                                          viewportMousePos.y);

            if (r_window.getInputHandler()
                    .getInput("secondaryAction1")
                    ->isDown())
            {

                Particle stone;
                float mult = Utils::Math::Random::weakRandInt(80, 100) / 100.0f;
                stone.setColor(Color(200 * mult, 205 * mult, 200 * mult));
                stone.setPhysicsType(Particle::PhysicsType::None);
                stone.setMatterType(Particle::MatterType::Solid);
                stone.getVerlet().setMass(200000000);

                m_world.getParticleHandler().draw(worldPos.x, worldPos.y, stone,
                                                  5);
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction2")
                    ->isDown())
            {
                Particle air;

                m_world.getParticleHandler().draw(worldPos.x, worldPos.y, air,
                                                  10);
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction3")
                    ->isDown())
            {
                Particle sand;
                float mult = Utils::Math::Random::weakRandInt(80, 100) / 100.0f;
                sand.setColor(Color(255 * mult, 235 * mult, 161 * mult));
                sand.setPhysicsType(Particle::PhysicsType::Sand);
                sand.setMatterType(Particle::MatterType::Solid);
                sand.setRestitution(0.1f);
                sand.getVerlet().setMass(1);

                m_world.getParticleHandler().draw(worldPos.x, worldPos.y, sand,
                                                  4);
            }

            if (r_input.getInput("left")->isDown())
            {
                m_player->getController().move(-5, 0);
            }
            if (r_input.getInput("right")->isDown())
            {
                m_player->getController().move(5, 0);
            }
            if (r_input.getInput("down")->isDown())
            {
                m_player->getController().move(0, 5);
            }
            if (r_input.getInput("up")->isDown())
            {
                m_player->getController().move(0, -5);
            }
            if (r_input.getInput("jump")->wasPressed())
            {
                m_player->getController().jump();
            }

            m_world.getParticleHandler().update(r_time.getDT());
            m_player->update(r_time.getDT());

            m_world.render(r_viewport, m_camera);
            m_player->render(r_viewport, m_camera);

            m_camera.setPosition(m_player->getController().getPosition().x,
                                 m_player->getController().getPosition().y);
        }

        return SceneID::Testing;
    }

  private:
    World m_world;
    Camera m_camera;
    std::unique_ptr<Player> m_player;
};
