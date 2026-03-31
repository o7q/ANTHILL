#include "testing.hpp"
#include "entities/wuskkogel/wuskkogel.hpp"
#include "math/random.hpp"
#include <memory>

void TestScene::onStart()
{
    m_world.getEntityHandler().addPlayer(std::make_unique<Player>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_input,
        r_assets));

    m_world.getEntityHandler().getCurrentPlayer()->getBody().setPosition(
        {0, -200});

    auto wuskkogel = std::make_unique<Wuskkogel>(
        m_world.getEntityHandler().getIDHandler().getNext(), r_assets);
    m_world.getEntityHandler().addEntity(std::move(wuskkogel));
}

void TestScene::onTick()
{
    Vec2i viewportMousePos =
        r_viewport.windowToViewportPosition(r_input.getMousePosition());
    Vec2i worldMousePos =
        m_world.getCamera().viewportToWorld(viewportMousePos, r_viewport);

    if (r_window.getInputHandler().getInput(InputID::AltAction1)->isDown())
    {
        Particle stone;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        stone.setColor(Color(200 * mult, 205 * mult, 200 * mult));
        stone.setPhysicsType(Particle::PhysicsType::None);
        stone.setMatterType(Particle::MatterType::Solid);
        stone.setMass(200000000);

        m_world.getParticleWorld().getEditor().draw(worldMousePos, stone, 20);
    }
    if (r_window.getInputHandler().getInput(InputID::AltAction2)->isDown())
    {
        Particle air;

        m_world.getParticleWorld().getEditor().draw(worldMousePos, air, 10);
    }
    if (r_window.getInputHandler().getInput(InputID::AltAction3)->isDown())
    {
        Particle sand;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        sand.setColor(Color(255 * mult, 235 * mult, 161 * mult));
        sand.setPhysicsType(Particle::PhysicsType::Sand);
        sand.setMatterType(Particle::MatterType::Solid);
        sand.setRestitution(0.1f);

        m_world.getParticleWorld().getEditor().draw(worldMousePos, sand, 4);
    }

    m_world.getEntityHandler().getCurrentPlayer()->updateAimPosition(
        worldMousePos);
    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        Vec2i playerPos = player->getBody().getPosition();
        m_world.getGenerator().generateInRadius(playerPos.toInt(), {20, 20});
        m_world.getCamera().setGoal(playerPos);
    }
    m_world.update(r_time.getDT());
    m_world.render(r_viewport, r_assets);

    Texture fpsText =
        r_assets.fonts()
            .get(FontID::Default)
            ->generateStringTexture(std::to_string((int)r_time.getFPS()),
                                    Color(0, 255, 0), 5, 1, 8);
    r_viewport.drawTexture(fpsText, {10, 5});

    if (Player *player = m_world.getEntityHandler().getCurrentPlayer())
    {
        Vec2f playerPos = player->getBody().getPositionFloat();
        Texture posTest =
            r_assets.fonts()
                .get(FontID::Default)
                ->generateStringTexture(std::to_string((int)playerPos.x) + " " +
                                            std::to_string((int)playerPos.y),
                                        Color(255, 255, 0), 5, 1, 8);
        r_viewport.drawTexture(posTest, {50, 5});
    }
}
