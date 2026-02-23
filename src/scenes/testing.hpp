#pragma once

#include "engine/camera.hpp"
#include "engine/math/random.hpp"
#include "engine/scene.hpp"
#include "engine/world/world.hpp"
#include <optional>
class TestScene : public Scene
{
  public:
    TestScene(Window &window) : Scene(window) {}

    std::optional<SceneID> update() override
    {
        if (start())
        {
            m_world.getParticleHandler().getDynamics().setUpdateInfo(
                Vec2<int>(4, 4), 5);
        }

        if (tick())
        {
            Vec2<float> mousePos =
                r_window.getInputHandler().getMousePosition();
            auto viewportMousePos = r_window.windowToViewportPosition(mousePos);

            if (r_window.getInputHandler().getInput("debugUp")->isDown())
            {
                m_camera.move(0, -1);
            }
            if (r_window.getInputHandler().getInput("debugDown")->isDown())
            {
                m_camera.move(0, 1);
            }
            if (r_window.getInputHandler().getInput("debugLeft")->isDown())
            {
                m_camera.move(-1, 0);
            }
            if (r_window.getInputHandler().getInput("debugRight")->isDown())
            {
                m_camera.move(1, 0);
            }

            if (r_window.getInputHandler()
                    .getInput("secondaryAction1")
                    ->isDown())
            {
                if (viewportMousePos.has_value())
                {
                    Vec2<unsigned int> pos = viewportMousePos.value();

                    Particle stone;
                    stone.setColor(Color(200, 200, 200));
                    stone.setPhysicsType(Particle::PhysicsType::None);
                    stone.setMatterType(Particle::MatterType::Solid);

                    m_world.getParticleHandler().draw(pos.x, pos.y, stone, 5);
                }
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction2")
                    ->isDown())
            {
                if (viewportMousePos.has_value())
                {
                    Vec2<unsigned int> pos = viewportMousePos.value();

                    Particle air;

                    m_world.getParticleHandler().draw(pos.x, pos.y, air, 10);
                }
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction3")
                    ->isDown())
            {
                if (viewportMousePos.has_value())
                {
                    Vec2<unsigned int> pos = viewportMousePos.value();

                    Particle sand;
                    sand.setColor(Color(20, Math::weakRandInt(50, 220), 100));
                    sand.setPhysicsType(Particle::PhysicsType::Sand);
                    sand.setMatterType(Particle::MatterType::Solid);
                    sand.setRestitution(0.5f);

                    m_world.getParticleHandler().draw(pos.x, pos.y, sand, 1);
                }
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction4")
                    ->isDown())
            {
                if (viewportMousePos.has_value())
                {
                    Vec2<unsigned int> pos = viewportMousePos.value();

                    Particle water;
                    water.setColor(Color(50, 50, 200));
                    water.setPhysicsType(Particle::PhysicsType::Water);
                    water.setMatterType(Particle::MatterType::Liquid);
                    water.setRestitution(0.05f);

                    m_world.getParticleHandler().draw(pos.x, pos.y, water, 10);
                }
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction5")
                    ->isDown())
            {
                if (viewportMousePos.has_value())
                {
                    Vec2<unsigned int> pos = viewportMousePos.value();

                    Particle smoke;
                    smoke.setColor(Color(200, 220, 200));
                    smoke.setPhysicsType(Particle::PhysicsType::Smoke);
                    smoke.setMatterType(Particle::MatterType::Gas);
                    smoke.setRestitution(0.0f);
                    smoke.getVerlet().setVelocity(
                        -1, 0, r_window.getTimeHandler().getDeltaTime());

                    m_world.getParticleHandler().draw(pos.x, pos.y, smoke, 10);
                }
            }

            if (r_window.getInputHandler().getInput("action1")->isDown())
            {
                if (viewportMousePos.has_value())
                {
                    Vec2<unsigned int> pos = viewportMousePos.value();
                    m_world.getParticleHandler().applyForce(pos.x, pos.y, 3.0f);
                }
            }

            m_world.getParticleHandler().update(
                r_window.getTimeHandler().getDeltaTime());

            m_world.render(r_window.getViewport(), m_camera);
        }

        return SceneID::Testing;
    }

  private:
    World m_world;
    Camera m_camera;
};
