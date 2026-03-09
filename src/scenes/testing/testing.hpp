#pragma once

#include "entity/ai/ai_entity.hpp"
#include "player/player.hpp"
#include "scene/scene.hpp"
#include "utils/math/random.hpp"
#include "world/world.hpp"
#include <iostream>
#include <memory>
#include <optional>

class TestScene : public Scene
{
  public:
    TestScene(Window &window) : Scene(window) {}

    std::optional<SceneID> update() override
    {
        if (start())
        {
            m_world.getEntityHandler().addPlayer(std::make_unique<Player>(
                m_world.getParticleHandler(), r_input));

            std::unique_ptr<AIEntity> test = std::make_unique<AIEntity>(
                m_world.getParticleHandler(),
                m_world.getEntityHandler().getCurrentPlayer());
            // test->getBody().setGravity(0.1f);

            m_world.getEntityHandler().addEntity(std::move(test));
        }

        if (tick())
        {
            Vec2<float> mousePos = r_input.getMousePosition();
            Vec2<int> viewportMousePos =
                r_viewport.windowToViewportPosition(mousePos);

            Vec2<int> worldPos = m_world.getCamera().viewportToWorld(
                viewportMousePos.x, viewportMousePos.y, r_viewport);

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
                stone.setImmovable(true);

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
            m_world.update(r_time.getDT());

            if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
            {
                m_world.getCamera().setGoal(player->getBody().getPosition().x,
                                            player->getBody().getPosition().y);

                m_world.getCamera().update(r_time.getDT());
            }

            m_world.render(r_viewport);

            // Vec2<int> start = {1, 1};
            // Vec2<int> end = {200, 200};

            std::cout << r_time.getFPS() << std::endl;
        }

        return SceneID::Testing;
    }

  private:
    World m_world;
};
