#include "testing.hpp"
#include "backend/viewport/render_command.hpp"
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

    for (int i = 0; i < 1; ++i)
    {
        auto wuskkogel = std::make_unique<Wuskkogel>(
            m_world.getEntityHandler().getIDHandler().getNext(), r_assets);
        wuskkogel->getBody().setPosition({i * 10, -20});
        m_world.getEntityHandler().addEntity(std::move(wuskkogel));
    }
}

void TestScene::onTick()
{
    std::vector<RenderCommand> renderCommands;

    m_camera.setViewSize(r_viewport.getSize());

    Vec2i viewportMousePos =
        r_viewport.windowToViewportPosition(r_input.getMousePosition());
    Vec2i worldMousePos = m_camera.viewportToCamera(viewportMousePos);

    if (r_window.getInputHandler().getInput(InputID::AltAction1)->isDown())
    {

        Particle stone;
        float mult = Math::Random::weakRandInt(80, 100) / 100.0f;
        stone.setColor(Color(200 * mult, 205 * mult, 200 * mult));
        stone.setPhysicsType(Particle::PhysicsType::None);
        stone.setMatterType(Particle::MatterType::Solid);
        stone.setMass(200000000);

        m_world.getParticleHandler().getEditor().draw(worldMousePos, stone, 20);
    }
    if (r_window.getInputHandler().getInput(InputID::AltAction2)->isDown())
    {
        Particle air;

        m_world.getParticleHandler().getEditor().draw(worldMousePos, air, 10);
    }

    Player *player = m_world.getEntityHandler().getCurrentPlayer();
    Vec2i updatePos;
    if (player)
    {
        player->updateAimPosition(worldMousePos);
        updatePos = player->getBody().getPosition();
    }

    m_generator.generate(updatePos.toInt());
    m_world.update(r_time.getDT(), updatePos, m_backendEvents);

    if (player)
    {
        player->updateAimPosition(worldMousePos);
        updatePos = player->getBody().getPosition();
    }
    m_camera.setGoal(updatePos);
    m_camera.update(r_time.getDT());

    m_world.render(m_camera, r_assets, renderCommands);

    renderText(renderCommands);

    r_viewport.render(renderCommands);
}
