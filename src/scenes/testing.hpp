#pragma once

#include "engine/camera.hpp"
#include "engine/math/random.hpp"
#include "engine/player/player.hpp"
#include "engine/scene.hpp"
#include "engine/world/world.hpp"
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
        }

        if (tick())
        {
            Vec2<float> mousePos =
                r_window.getInputHandler().getMousePosition();
            Vec2<int> viewportMousePos =
                r_window.getViewport().windowToViewportPosition(mousePos);

            Vec2<float> worldPos = m_camera.viewportToWorld(viewportMousePos.x,
                                                            viewportMousePos.y);

            Particle p;
            p.setPhysicsType(Particle::PhysicsType::None);
            p.setMatterType(Particle::MatterType::Solid);
            p.setColor(Color(255, 255, 255));
            m_world.getParticleHandler().set(0, 0, p);

            m_world.getParticleHandler().getDynamics().setUpdateInfo(
                m_camera.getPosition().x, m_camera.getPosition().y, 10);

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
                Particle stone;
                stone.setColor(Color(200, 200, 200));
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
                sand.setColor(Color(20, Math::weakRandInt(50, 220), 100));
                sand.setPhysicsType(Particle::PhysicsType::Sand);
                sand.setMatterType(Particle::MatterType::Solid);
                sand.setRestitution(0.7f);
                sand.getVerlet().setMass(1);

                m_world.getParticleHandler().draw(worldPos.x, worldPos.y, sand,
                                                  4);
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction4")
                    ->isDown())
            {
                Particle water;
                water.setColor(Color(50, 50, 200));
                water.setPhysicsType(Particle::PhysicsType::Water);
                water.setMatterType(Particle::MatterType::Liquid);
                water.setRestitution(0);

                m_world.getParticleHandler().draw(worldPos.x, worldPos.y, water,
                                                  10);
            }
            if (r_window.getInputHandler()
                    .getInput("secondaryAction5")
                    ->isDown())
            {
                Particle smoke;
                smoke.setColor(Color(200, 220, 200));
                smoke.setPhysicsType(Particle::PhysicsType::Smoke);
                smoke.setMatterType(Particle::MatterType::Gas);
                smoke.setRestitution(0.0f);
                smoke.getVerlet().setVelocity(
                    -1, 0, r_window.getTimeHandler().getDeltaTime());

                m_world.getParticleHandler().draw(worldPos.x, worldPos.y, smoke,
                                                  10);
            }

            if (r_window.getInputHandler().getInput("action1")->isDown())
            {
                m_world.getParticleHandler().applyForce(
                    worldPos.x, worldPos.y, 10.0f,
                    r_window.getTimeHandler().getDeltaTime());
            }

            m_world.getParticleHandler().update(
                r_window.getTimeHandler().getDeltaTime());

            m_world.render(r_window.getViewport(), m_camera);

            m_player.render(r_window.getViewport(), m_camera);
        }

        return SceneID::Testing;
    }

  private:
    World m_world;
    Camera m_camera;
    Player m_player;
};
