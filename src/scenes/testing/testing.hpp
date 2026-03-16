#pragma once

#include "entities/test.hpp"
#include "player/player.hpp"
#include "scene/scene.hpp"
#include "utils/math/angle.hpp"
#include "utils/math/random.hpp"
#include "utils/rectangle.hpp"
#include "utils/render.hpp"
#include "world/world.hpp"
#include <memory>
#include <optional>

class TestScene : public Scene
{
  public:
    TestScene(Window &window) : Scene(window), m_testTexture("carter.png") {}

    std::optional<SceneID> update() override
    {
        if (start())
        {
            m_world.getEntityHandler().addPlayer(
                std::make_unique<Player>(r_input));

            for (int i = 0; i < 1; ++i)
            {
                std::unique_ptr<TestEntity> test =
                    std::make_unique<TestEntity>();

                test->getBody().setPosition(5 * i, 0);

                m_world.getEntityHandler().addEntity(std::move(test));
            }

            Particle stone;
            stone.setColor(Color(200, 205, 200));
            stone.setPhysicsType(Particle::PhysicsType::None);
            stone.setMatterType(Particle::MatterType::Solid);
            stone.getVerlet().setMass(200000000);
            stone.setImmovable(true);

            m_world.getParticleHandler().draw(0, 300, stone, 150);

            for (int i = 0; i < 1000; ++i)
            {
                int sign = Utils::Math::Random::weakRandInt(0, 2) == 0 ? -1 : 1;

                m_world.getParticleHandler().draw(
                    sign * Utils::Math::Random::weakRandInt(50, 1000),
                    Utils::Math::Random::weakRandInt(300, 400), stone, 30);
            }
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
                                                  20);
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

                Vec2<int> pos = m_world.getEntityHandler().getLatestEntity()->getBody().getPosition();

            m_world.render(r_viewport);
            Utils::Render::drawTexture(r_viewport, m_testTexture, m_world.getCamera().worldToViewport(pos.x, pos.y, r_viewport));
        }

        // std::cout << static_cast<int>(r_time.getFPS()) << std::endl;

        return SceneID::Testing;
    }

  private:
    World m_world;
    Texture m_testTexture;
};
